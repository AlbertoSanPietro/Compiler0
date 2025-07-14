%{
#include <stdio.h>
#include <stdlib.h>
#include "codegen.h"

extern int yylex(void);
extern int yyparse(void);
void yyerror(const char *s) { fprintf(stderr, "Parse error: %s\n", s); exit(1); }
%}

%union {
    int ival;
    char* sval;
    struct ASTNode* node;
}

%token INT MAIN IF ELSE WHILE RETURN
%token EQ NEQ LE GE LT GT
%token <ival> NUMBER
%token <sval> IDENT

%type <node> Program Function Stmt StmtList Expr

%left EQ NEQ LT GT LE GE
%left '+' '-'
%left '*' '/' '%'

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE


%%

Program: Function { generate_code($1); }
;

Function: INT MAIN '(' ')' '{' StmtList '}' { $$ = make_function($6); }
;

StmtList: Stmt { $$ = make_stmt_list(NULL, $1); }
        | StmtList Stmt { $$ = make_stmt_list($1, $2); }
;

Stmt:
      INT IDENT '=' Expr ';' { $$ = make_var_decl($2, $4); }
    | IDENT '=' Expr ';'     { $$ = make_assignment($1, $3); }
    | IF '(' Expr ')' Stmt %prec LOWER_THAN_ELSE { $$ = make_if($3, $5, NULL); }
    | IF '(' Expr ')' Stmt ELSE Stmt { $$ = make_if($3, $5, $7); }
    | WHILE '(' Expr ')' Stmt { $$ = make_while($3, $5); }
    | RETURN Expr ';' { $$ = make_return($2); }
    | '{' StmtList '}' { $$ = $2; }
;


Expr:
      NUMBER { $$ = make_number($1); }
    | IDENT { $$ = make_variable($1); }
    | Expr '+' Expr { $$ = make_binop("+", $1, $3); }
    | Expr '-' Expr { $$ = make_binop("-", $1, $3); }
    | Expr '*' Expr { $$ = make_binop("*", $1, $3); }
    | Expr '/' Expr { $$ = make_binop("/", $1, $3); }
    | Expr '%' Expr { $$ = make_binop("%", $1, $3); }
    | Expr EQ Expr  { $$ = make_binop("==", $1, $3); }
    | Expr NEQ Expr { $$ = make_binop("!=", $1, $3); }
    | Expr LT Expr  { $$ = make_binop("<", $1, $3); }
    | Expr LE Expr  { $$ = make_binop("<=", $1, $3); }
    | Expr GT Expr  { $$ = make_binop(">", $1, $3); }
    | Expr GE Expr  { $$ = make_binop(">=", $1, $3); }
    | '(' Expr ')' { $$ = $2; }
;

%%

