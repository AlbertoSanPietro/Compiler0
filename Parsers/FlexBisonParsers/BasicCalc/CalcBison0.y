%{
#include <stdio.h>
%}

//token declaration:
%token	NUMBER 
%token ADD SUB MUL DIV ABS
%token EOL


%%

calclist:
	| calclist exo EOL {	printf("=%d\n", $1); }
	;
exp: factor
	| exp ADD factor {	$$ = $1 + $3; }
	| exp SUB factor {	$$ = $1 - $3; }
	;

factor: term
	| factor MUL term { $$ = $1 * $3; }
	|	factor DIV term { $$ = $1 / $3; }
	;

term: NUMBER 
	|	ABS term { $$ = $2 >= 0? $2 : - $2; }
	;
%%

int main(int argc, char **argv) 
{
	yyparse();
}

