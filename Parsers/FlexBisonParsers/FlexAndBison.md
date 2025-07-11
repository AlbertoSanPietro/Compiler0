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


```










