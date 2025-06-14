%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);
%}

%union {
    int ival;
    char* sval;
}

%token INT RETURN IF ELSE WHILE
%token EQ NEQ LE GE LT GT
%token <ival> NUMBER
%token <sval> IDENT

%type <ival> expr

%start program

%%

program:
    function
;

function:
    INT main_header '{' stmt_list '}' {
        printf("Parsed main() successfully.\n");
    }
;

main_header:
    IDENT '(' ')' {
        if (strcmp($1, "main") != 0) {
            yyerror("Only 'main' function is allowed.");
            exit(1);
        }
    }
;

stmt_list:
    /* empty */
  | stmt_list statement
;

statement:
    decl_stmt
  | assign_stmt
  | if_stmt
  | while_stmt
  | return_stmt
  | ';'
;

decl_stmt:
    INT IDENT ';' {
        printf("Declare int %s\n", $2);
        free($2);
    }
;

assign_stmt:
    IDENT '=' expr ';' {
        printf("Assign to %s\n", $1);
        free($1);
    }
;

if_stmt:
    IF '(' expr ')' statement
  | IF '(' expr ')' statement ELSE statement
;

while_stmt:
    WHILE '(' expr ')' statement
;

return_stmt:
    RETURN expr ';'
;

expr:
    expr '+' expr    { $$ = $1 + $3; }
  | expr '-' expr    { $$ = $1 - $3; }
  | expr '*' expr    { $$ = $1 * $3; }
  | expr '/' expr    { $$ = $1 / $3; }
  | expr '%' expr    { $$ = $1 % $3; }
  | expr EQ expr     { $$ = $1 == $3; }
  | expr NEQ expr    { $$ = $1 != $3; }
  | expr LE expr     { $$ = $1 <= $3; }
  | expr GE expr     { $$ = $1 >= $3; }
  | expr LT expr     { $$ = $1 < $3; }
  | expr GT expr     { $$ = $1 > $3; }
  | '(' expr ')'     { $$ = $2; }
  | NUMBER           { $$ = $1; }
;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

