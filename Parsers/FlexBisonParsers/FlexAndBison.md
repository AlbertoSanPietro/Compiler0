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












