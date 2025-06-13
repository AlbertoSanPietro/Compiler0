/* parser.y – Bison grammar */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* helper to enforce only `main` is defined */
void enforce_main(const char* name) {
    if (strcmp(name, "main") != 0) {
        fprintf(stderr, "Error: only `main` may be defined, not `%s`\n", name);
        exit(1);
    }
}

int yylex(void);
void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}
%}

/* ——————————————————————————————————————————— */
/* 1) Tokens and their value types             */
/* ——————————————————————————————————————————— */

%union {
    int    ival;
    char  *sval;
}

%token <ival>    NUMBER
%token <sval>    IDENTIFIER
%token           INT RETURN IF ELSE WHILE
%token           EQ NE LE GE

/* precedence and associativity */
%nonassoc ELSE        /* for dangling‐else */
%nonassoc IFX         /* pseudo‐token for if without else */
%left '='
%left EQ NE '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'

%start program

%%

/* ——————————————————————————————————————————— */
/* 2) Grammar rules                              */
/* ——————————————————————————————————————————— */

program
    : function_definition
    ;

function_definition
    : INT IDENTIFIER '(' ')' compound_statement
        {
            enforce_main($2);
            /* at runtime you'd build an AST or emit code here */
        }
    ;

compound_statement
    : '{' stmt_list '}'
    ;

stmt_list
    : /* empty */
    | stmt_list statement
    ;

statement
    : declaration
    | assignment
    | if_statement
    | while_statement
    | return_statement
    | ';'                      /* empty statement */
    ;

declaration
    : INT IDENTIFIER opt_init ';'
    ;

opt_init
    : /* empty */
    | '=' expression
    ;

assignment
    : IDENTIFIER '=' expression ';'
    ;

if_statement
    : IF '(' expression ')' statement %prec IFX
    | IF '(' expression ')' statement ELSE statement
    ;

while_statement
    : WHILE '(' expression ')' statement
    ;

return_statement
    : RETURN expression ';'
    ;

expression
    : expression '+' expression
    | expression '-' expression
    | expression '*' expression
    | expression '/' expression
    | expression '%' expression
    | expression EQ expression
    | expression NE expression
    | expression '<' expression
    | expression '>' expression
    | expression LE expression
    | expression GE expression
    | '(' expression ')'
    | IDENTIFIER
    | NUMBER
    ;

%%

int main(void) {
    return yyparse();
}

