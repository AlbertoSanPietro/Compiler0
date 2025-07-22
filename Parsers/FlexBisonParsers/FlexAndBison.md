_Questo è un breve markdown sull'uso di flex e bison di base; la fonte è:
"Flex & Bison - Unix Test Processing tools" di John Levine_

# Introduzione
Flex e Bison sono tools per costrutire programmi che gestiscano input strutturato, anche al di fuori dei compilatori. 
Una delle chiavi della compilazione fu la divisione tra analisi lessicale (lexing) e l'analisi sintattica (parsing).
Lo scanning divide l'input in pezzi significativi (tokens) e il parsing capisce come i token sono legati tra loro.
`alpha = beta + gamma`
Lo scanner divide in `alpha, equal sign, beta, plus sign, gamma, semicolon`
Il parser capisce che si tratta di una espressione assegnata ad `alpha`.

Un modo comodo per descrivere i pattern che dobbiamo gestire sono le regex o regexp.
Un programma flex è una serie di regexps con le istruzioni (azioni) che descrivono cosa fare in caso di pattern matching. Flex usa degli automi a stati finiti ed è estremamente efficiente.
Il primo programma si trova in BasicWc.l
Si tratta di un contatore di caratteri, parole e linee da stdin.

```
/* just like Unix wc */
%{
int chars = 0;
int words = 0;
int lines = 0;
%}
%%
[a-zA-Z]+   { words++; chars += strlen(yytext); }

\n          { chars++; lines++; }

.           { chars++; }
%%
main(int argc, char **argv)
{
yylex();
printf("%8d%8d%8d\n", lines, words, chars);
}
```

Il programma è diviso in 3, ed è separato da "%%".

Il codice dentro %{%} è praticamente C
Nella seconda sezione abbiamo pattern ed azioni.
Abbiamo 3 patterns, e il primo [a-zA-Z]+ cerca una parola; il segno + ci dice di matchare una o più delle "cose" precedenti.
Il secondo pattern \n matcha con una newline.
Il "." invece vuol dire per qualsiasi carattere. 

## Mettere insieme Flex e Bison
Possiamo scrivere un calcolatore per mettere insieme Flex e Bison. Iniziamo con Flex:
``` 
%%
"+"			{ printf("PLUS\n"); }
"-"			{ printf("MINUS\n"); }
"*"			{ printf("TIMES\n"); }
"/"			{ printf("DIVIDE\n"); }
"|"			{ printf("ABS\n"); }
[0-9]+	{ printf("NUMBER %s\n", yytext); }
\n			{ printf("NEWLINE\n"); }
[ \t]		{ }
.				{ printf("Mistery character %s\n", yytext); }

%%
```
Ogni volta che al programma serve un token chiama _yylex()_, facendo comportare lo scanner come una coroutine. La scansione continua finché non si trova un token da ritornare con la stessa chiamata. 
Quando flex ritorna ci da un token e il valore del token. Quando bison crea un parser assegna ad ogni token un valore numerico superiore a 258 come in un enum.
Scriviamo a mano allora i token per il calcolatore:
(Il sorgente è CalcEnum.l)
```
%{
enum yytokentype {
	NUMBER = 258,
	ADD = 259,
	SUB = 260,
	MUL = 261,
	DIV = 262,
	ABS = 263,
	EOL = 264

};

int yylval;

%}


%%
"+"			{ return ADD;}
"-"			{ return SUB;}
"*"			{ return MUL;}
"/"			{ return DIV;}
"|"			{ return ABS;}
[0-9]+	{ yylval = atoi(yytext); return NUMBER; }
\n			{ return EOL;}
[ \t]		{ }
.				{ printf("Mistery character %c\n", *yytext); }

%%

int main(int argc, char **argv) {
	int tok;

	while(tok = yylex()) {
		printf("%d", tok);
		if(tok == NUMBER) printf(" =%d\n", yylval);
		else printf("\n");
	}
}
```
Possiamo passare al parsing.
Un modo classico per rappresentare il parsing è un parse tree. Nel tree dobbiamo tenere conto delle precedenze degli operatori per esempio. 
Il tipo di grammatica più comune da gestire è la CFG (Context-Free-Grammar), scritta in BNF (Backus-Naur Form). 
Il BNF è semplice: ogni linea è una regola che dice come creare un ramo dell'albero;
_::=_ può essere letto come "è un" o "diventa" _|_ è un "oppure".
Il nome della èarte sinistra di una regola è un simbolo; tutti i token sono simboli, ma non viceversa. 
Per gestire:
_1 * 2 + 3 * 4 5_ :
```
<exp> ::= <factor>
        | <exp> + <factor>
<factor> ::= NUMBER 
        | <factor> * NUMBER
```

Le regole di Bison sono un BNF con sintassi semplificata.
Di seguito il bison per il nostro calcolatore:
(src: CalcBison0.y)
```
%{
//C includes
#include <stdio.h>
%}

//token declaration:
%token	NUMBER 
%token ADD SUB MUL DIV ABS
%token EOL


%%

calclist:
	| calclist exp EOL {	printf("=%d\n", $1); }
	;
exp: factor
	| exp ADD factor {	$$ = $1 + $3; }
	| exp SUB factor {	$$ = $1 - $3; }
	;

factor: term
	| factor MUL term { $$ = $1 * $3; }
	| factor DIV term { $$ = $1 / $3; }
	;

term: NUMBER 
	|	ABS term { $$ = $2 >= 0? $2 : - $2; }
	;
%%
//C code to be executed
int main(int argc, char **argv) 
{
	yyparse();
}

yyerror(char *s) 
{
fprintf(stderr, "error: %s\n", s);	
}
```
I programmi Bison sono divisi in tre come i programmi Flex.
All'inizio dichiarazione e `#include`, nell parte centrale le dichiarazioni dei token tramite
`%token`
I token sono scritti in maiuscolo per convenzione. 
La seconda sezione contiene le regole BNF semplificate. Bison gestisce, oltre al parsing, anche la generazione di strutture dati utili o la stampa di risultati (sotto). 
I simboli hanno un valore:
Il valore del simbolo target (a sx) è: `$$`, i simboli a dx sono in ordine: `$1, $2, $3 ...`
I valori dei token sono ciò che era in yyval quando lo scanner ha ritornato il token. Il valore degli altri simboli arriva dalle regole. 

In questo parser le regole di _calcset_ implementano un loop che legge un'espressione terminata da newline e ne stampa il valore. 
Le altre regole implementano il calcolatore. 

## Compilare insieme Flex e Bison
Per chiamare Bison dal Lexer semplicemente cambiamo la prima parte, scrivendo:
```
%{
#include "CalcBison0.tab.h"
%}
```
Il resto rimane uguale. Per la compilazione ci sono diversi Instructions.md nella repo.

## Grammatiche ambigue
E' legittimo chiedersi perché siamo stati così pedanti prima; avremmo potuto scrivere:

```
exp:    exp ADD exp
    |   exp SUB exp
    |   exp MUL exp
    |   exp DIV exp
    |   ABS exp
    |   NUMBER
    ;
```
Le ragioni sono precedenze ed ambiguità. La separazione dei simboli dà la precedenza alle operazioniPotremmo quindi scrivere:
```
exp:    exp ADD exp
    |   exp SUB exp
    |   factor
    ;
```
No. Questa è una grammatica ambigua poiché non specifica se prima si fa l'addizione o la sottrazione, Bison NON parsa grammatiche ambigue.

## Aggiunta di regole
Una delle cose comode è che fare aggiustamenti alle grammatiche è spesso semplice.
Sarebbe comodo se il calcolatore gestisse le parentesi o i commenti con '//'
Ci basta aggiungere una singola regola al parser e tre allo scanner.
```
//nella sezione delle dichiarazioni:
%token OP CP 
/* */ 

%%
term: NUMBER
    |   ABS term { $$ = $2 >= 0? $2 : - $2; }
    |   OP exp CP { $$ = $2; } //Nuova regola
```
Aggiungiamo le regole al lexer (o scanner):
```
"("    { return OP; }
")"    { return CP; }
"//".*  /*Ignora i commenti*/
```
Finito.

I file si possono trovare nelle rispettive directories.



# Usare flex

## Regex 
Flex usa le regex, prendendo le regex POSIX ed estendendole. 
I significati dei simboli sono:
* _._
Matcha ogni carattere ad eccezione della newline.

* _[]_
Una classe di caratteri che matcha qualsiasi carattere all'interno delle parentesi.
Se il primo char è _^ (circonflesso)_ il significato diventa matchare tutto tranne ciò che è nelle parentesi. Il dash _-_ è un range: [0-9] corrisponde a [0123456789].
[a-z] Vuol dire qualsiasi carattere minuscolo. 

* _[a-z]{-}[jv]_
Una classe di caratteri differenziati in cui i caratteri nella prima classe omettono i caratteri nella seconda classe.

* _^_
Matcha l'inizio di una linea come primo carattere di una regex. Dentro le _[]_ è la negazione.

* _$_ 
Matcha la fine di una linea come ultimo carattere di una regex.

* _{}_
Se contengono 1 o 2 numeri indicano il numero massimo e minimo che il pattern precedente può matchare. _A{1,3}_ Matcha da una a tre lettere A e _0{5}_ matcha 00000
_\_ 
Usato come in C, ma \* è l'asterisco.

_*_ 
Matcha 0 o più copie dell'spressione precedente. _[ \t]*_ è un pattern comune per matchare spazi o tab opzionali o stringhe vuote.

_+_ 
Matcha una o più occorrenze della regex precedente. Per esempio _[0-9]+_ matcha stringe di cifre come _1, 111 o 123456_ ma non stringhe vuote.

_?_
Matcha zero o una occorrenza della regex precedente:

_-?[0-9]+_ matcha un numero segnato includendo il segno _-_ opzionale all'inizio.

_ | _ 
Operatore di alternanza; matcha o la regex precedente o quella successiva.
_faith|hope|charity_ matcha ognuna delle 3 virtù.

_"..."_
Qualsiasi cosa tra virgolette è trattato letteralmente, spesso si usa per la punteggiatura.

_()_
Raggruppa una serie di regex in una nuova regex unica.
_(01)_ matcha la sequenza 01 e _a(bc|de)_ matcha abc o ade.

_/_
Trailing context. matcha la regex che precede lo slash ma solo se seguita dalla regex dopo lo slash.
Per esempio _0/1_ matcha 0 nella stringa 01 ma non matcherebbe nulla nella stringa 0 o 02.
Il materiale matchato dal pattern che segue lo slash non è "consumato", rimane e può essere trasformato in token sequenziali. Solo una slash è permessa per pattern.

L'operatore di ripetizione ha effetto sulla espressione più piccola precedente, quindi
_abc+_ matcha _ab_ seguito da uno o più _c_, per esempio 
_(abc+)_ matcha una o più ripetizioni di _abc_.

Piccolo extra:
validazione di una email di tipo:
_josh.doe@gmail.com_

_foo_bar@gmail.com_

_Giovanni165@gmail.com_ 

`^[a-zA-Z0-9._%+-]+@gmail.com\.com$`

## Come flex gestisce i pattern ambigui 
I programmi di flex sono ambigui e quindi ci sono 2 regole che vengono seguite per risolvere tale ambiguità:
1)matcha la stringa più lunga possibile
2)nel caso di un pareggio usa il pattern che appare per primo nel programma.


## File I/O negli scanner Flex
Flex legge sta stdin a meno che non venga esplicitato il contrario. Di base usa `yyin` per aprire file e stdin, quindi mettendo nel nostro main `int argc char **argv` possiamo aprire un file singolo:

```
/* even more like Unix wc */
%option noyywrap
%{
int chars = 0;
int words = 0;
int lines = 0;
%}

%%

[a-zA-Z]+   { words++; chars += strlen(yytext); }
\n          { chars++; lines++; }
.           { chars++; }

%%

main(argc, argv)
int argc;
char **argv;
{
    if(argc > 1) {
        if(!(yyin = fopen(argv[1], "r"))) {
            perror(argv[1]);
            return (1);
            }
        }
    yylex();
    printf("%8d%8d%8d\n", lines, words, chars);
}
```
 The real version of _wc_ reads several files so we have to change our lexer a bit.

 ```
%option noyywrap

%{
int chars = 0;
int words = 0;
int lines = 0;

int totchars = 0;
int totwords = 0;
int totlines = 0;
%}

%%

[a-zA-Z]+   { words++; chars += strlen(yytext); }
\n          { chars++; lines++; }
.           { chars++; }

%%

int main(int argc, char **argv)
{
    int i=0;

    if(argc < 2) { /*read stdin*/ 
    yylex();
    printf("%8d%8d%8d\n", lines, words, chars);
    return 0;
    }

    for (i=1; i < argc; i++) {
        FILE *f = fopen(argv[i], "r");

        if (!f) {
            perror(argv[i]);
            return (1);
        }

        yyrestart(f);
        yylex();
        fclose(f);
        printf("%8d%8d%8d %s\n", lines, words, chars, argv[i]);
        totchars += chars; chars = 0;
        totwords += words; words = 0;
        totlines += lines; lines = 0;
    }
    if (argc > 1) //print total if more than  one file
        printf("%8d%8d%8d total\n", totlines, totwords, totchars);
    return 0;
}
 ```

## Input ad uno scanner Flex
E' estremamente raro che uno scanner flex sia fonte di un bottleneck di performance. 
Per gestire gli input Flex usa una struttura _YY_BUFFER_STATE_ che descrive una singola sorgente di input. 

_qui si va in specifiche inutili per la comprensione del progetto_

## Output di uno scanner Flex
La gestione dell'output è semplice e completamenze opzionale. Di default Flex copia l'input non matchato su _yyout_

## Stati di partenza e File di input nestati
Mettiamo a frutto la nostra conoscenza dell'I/O di Flex con un progrmma che gestisce file include nestati e li stampa insieme al numero di linea del file.
Teniamo una stack di file di input e numeri di linea pushando ad ogni #include e poppando ad EOF. 
Usiamo anche gli _start states_ (stati di partenza) che ci fanno controllare quali pattern possono essere matchati quando. La linea _%x_ in cima la file denisice _IFILE_ come uno stato di partenza. 
Si possono definire quanti stati di partena si vogliono. 
La _%x_ segna IFILE come start state esclusivo ( _exclusive_ ). 
La macro _BEGIN_ passa ad uno stato di partenza differente.

```
%option noyywrap
%x IFILE

%{
#include <stdio.h>
#include <stdlib.h>

struct bufstack {
    struct bufstack *prev;
    YY_BUFFER_STATE bs;
    int lineno;
    char *filename;
    FILE *f;
} *curbs = 0;

char *curfilename; /* name of current input file */

int newfile(char *fn);
int popfile(void);
/*int yylineno = 1;*/
%}

%%

^"#[ \t]*include[ \t]*[\"<]"[^"]+[">"]? {
    BEGIN IFILE;
}

<IFILE>[^ \t\n\">]+ {
    int c;
    while ((c = input()) && c != '\n');
    yylineno++;
    if (!newfile(yytext))
        yyterminate(); /* no such file */
    BEGIN INITIAL;
}

<IFILE>.|\n {
    fprintf(stderr, "%4d bad include line\n", yylineno);
    yyterminate();
}

<<EOF>> {
    if (!popfile())
        yyterminate();
}

^. {
    fprintf(yyout, "%4d %s", yylineno, yytext);
}

^\n {
    fprintf(yyout, "%4d %s", yylineno++, yytext);
}

\n {
    ECHO;
    yylineno++;
}

. {
    ECHO;
}

%%

int main(int argc, char **argv)
{
    if (argc < 2) {
        fprintf(stderr, "need filename\n");
        return 1;
    }
    if (newfile(argv[1]))
        yylex();
    return 0;
}

int newfile(char *fn)
{
    FILE *f = fopen(fn, "r");
    struct bufstack *bs = malloc(sizeof(struct bufstack));

    if (!f) {
        perror(fn);
        return 0;
    }

    if (!bs) {
        perror("malloc");
        exit(1);
    }

    if (curbs)
        curbs->lineno = yylineno;

    bs->prev = curbs;
    bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
    bs->f = f;
    bs->filename = fn;

    yy_switch_to_buffer(bs->bs);
    curbs = bs;
    yylineno = 1;
    curfilename = fn;

    return 1;
}

int popfile(void)
{
    struct bufstack *bs = curbs;
    struct bufstack *prevbs;

    if (!bs)
        return 0;

    fclose(bs->f);
    yy_delete_buffer(bs->bs);

    prevbs = bs->prev;
    free(bs);

    if (!prevbs)
        return 0;

    yy_switch_to_buffer(prevbs->bs);
    curbs = prevbs;
    yylineno = curbs->lineno;
    curfilename = curbs->filename;

    return 1;
}

```

La prima parte del programma definisce lo stato iniziale e dichiara la struttura _bufstack_ che mantiene una entry nella lista degli input salvati.
Il primo pattern che matcha un _#include_ fino alle doppie virgolette che precedono il filename.  

Il pattern permette di avere del whitespace opzionale e cambia lo stato di IFILE per leggere il prossimo filename di input. Nello stato IFILE il secondo pattern matcha un filename, caratteri fino alle virgolette chiuse, spazio o EOL. Tuttavia dobbiamo gestire quello che rimano della linea con _#include_. Usiamo _input()_: un loop legge fino a EOL o EOF e continua dalla linea successiva una volta che si è usciti dal file incluso.
Uno start state deve gestire qualsiasi input possibile, quindi per gestire gli erorri usiamo la macro _yyterminate()_ per ritornare dallo scanner. 
Il pattern _<<EOF>>__  matcha alla fine do ogni file fi input. Chiamiamo _popfile()_ per tironare al file precedente. Gli altri pattern scrivono le linee con il loro numero usando _yylineno_

La routine _newfile(fn)_ si preparala e leggere da un file _fn_ salvando i file di input precedenti in una linked list di strutture _bufstack_. 

La routine _popfile()_ fa il contrario di _newfile_. 


## Tabelle dei Simboli e Concordance Generator
Quasi tutti i programmi di flex e bison usano una tabella dei simboli per mantenere traccia dei nomi usati nell'input. Iniziamo con un programma semplice che fa una concordance: una lista dei nmeri di linea dove ogni parola dell'input appare.

### Gestire le tabelle dei simboli

```
/* text concordance */
%option noyywrap nodefault yylineno case-insensitive
/* the symbol table */ 
%{
#include <stdio.h>

struct symbol {
	char *name;
	struct ref *reflist;
};

struct ref {
	struct ref *next;
	char *filename;
	int flags;
	int lineno;
};

//Simple symtab of fixed size
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char *);
void addref(int char *, char *, int);

char *curfilename;


%}

/*Rules and skip common words*/

%%



a |
an |
and |
are |
as |
at |
be | 
but |
for |
in |
is |
it |
of |
on |
or |
that |
the |
this |
to  /*ignore*/

[a-z]+(\'(s|t))? { addref(yylineno, curfilename, yytext, 0); }
.|\n /*Ignore everything else*/

%%

int main(int argc, char **argv) {
	int i;

	if (argc<2) {
		//read stdin
		curfilename = "(stdin)";
		yylineno = 1;
		yylex();
	} else {
			for (i = 1; i < argc; i++) {
				FILE *f= fopen(argv[i], "r");

				if (!f) {
					perror(argv[1]);
					return (1);
				}
				curfilename = argv[i]; //for addref

				yyrestart(f);
				yylineno= 1;
				yylex();
				fclose(f);
			}

			printrefs();
	}
}
```





































