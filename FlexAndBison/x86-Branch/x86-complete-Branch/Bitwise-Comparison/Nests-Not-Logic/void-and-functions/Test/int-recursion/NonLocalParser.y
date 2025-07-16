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
%token LSHIFT RSHIFT
%token AND OR XOR
%token NOT
%token VOID
%token ANDAND OROR LNOT

%token <ival> NUMBER
%token <sval> IDENT

%type <node> Program Stmt StmtList Expr
%type <node> Function ParamListOpt ParamList
%type <node> ArgList ArgListOpt

%left OR
%left XOR
%left AND
%left EQ NEQ
%left LT GT LE GE
%left LSHIFT RSHIFT
%left '+' '-'
%left '*' '/' '%'
%left OROR
%left ANDAND
%right LNOT

%precedence UMINUS UNOT
%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%

Program:
      Function                   { $$ = $1; generate_code($1); }
    | Program Function           { $$ = $2; generate_code($2); }
;

Function:
      INT MAIN '(' ParamListOpt ')' '{' StmtList '}'   { $$ = make_function("main", $4, $7); }
    | INT IDENT '(' ParamListOpt ')' '{' StmtList '}'  { $$ = make_function($2, $4, $7); }
    | VOID IDENT '(' ParamListOpt ')' '{' StmtList '}' { $$ = make_function($2, $4, $7); }
;
 
ParamListOpt:
      /* empty */               { $$ = NULL; }
    | ParamList                 { $$ = $1; }
    | VOID                      { $$ = NULL; }
;

ParamList:
      INT IDENT                         { $$ = make_param_list(NULL, make_var_decl($2, NULL)); }
    | ParamList ',' INT IDENT          { $$ = make_param_list($1, make_var_decl($4, NULL)); }
;

StmtList:
      Stmt                             { $$ = make_stmt_list(NULL, $1); }
    | StmtList Stmt                    { $$ = make_stmt_list($1, $2); }
;

Stmt:
      INT IDENT '=' Expr ';'          { $$ = make_var_decl($2, $4); }
    | IDENT '=' Expr ';'              { $$ = make_assignment($1, $3); }
    | IDENT '(' ArgListOpt ')' ';'    { $$ = make_function_call($1, $3); }
    | IF '(' Expr ')' Stmt %prec LOWER_THAN_ELSE { $$ = make_if($3, $5, NULL); }
    | IF '(' Expr ')' Stmt ELSE Stmt  { $$ = make_if($3, $5, $7); }
    | WHILE '(' Expr ')' Stmt         { $$ = make_while($3, $5); }
    | RETURN Expr ';'                 { $$ = make_return($2); }
    | RETURN ';'                      { $$ = make_return(NULL); }
    | '{' StmtList '}'                { $$ = $2; }
;

ArgListOpt:
      /* empty */                     { $$ = NULL; }
    | ArgList                         { $$ = $1; }
;

ArgList:
      Expr                            { $$ = make_expr_list(NULL, $1); }
    | ArgList ',' Expr                { $$ = make_expr_list($1, $3); }
;

Expr:
      NUMBER                          { $$ = make_number($1); }
    | IDENT                           { $$ = make_variable($1); }
    | IDENT '(' ArgListOpt ')'        { $$ = make_function_call($1, $3); }  
    | Expr '+' Expr                   { $$ = make_binop("+", $1, $3); }
    | Expr '-' Expr                   { $$ = make_binop("-", $1, $3); }
    | Expr '*' Expr                   { $$ = make_binop("*", $1, $3); }
    | Expr '/' Expr                   { $$ = make_binop("/", $1, $3); }
    | Expr '%' Expr                   { $$ = make_binop("%", $1, $3); }

    | Expr EQ Expr                    { $$ = make_binop("==", $1, $3); }
    | Expr NEQ Expr                   { $$ = make_binop("!=", $1, $3); }
    | Expr LT Expr                    { $$ = make_binop("<", $1, $3); }
    | Expr LE Expr                    { $$ = make_binop("<=", $1, $3); }
    | Expr GT Expr                    { $$ = make_binop(">", $1, $3); }
    | Expr GE Expr                    { $$ = make_binop(">=", $1, $3); }

    | Expr AND Expr                   { $$ = make_binop("&", $1, $3); }
    | Expr OR Expr                    { $$ = make_binop("|", $1, $3); }
    | Expr XOR Expr                   { $$ = make_binop("^", $1, $3); }
    | Expr LSHIFT Expr                { $$ = make_binop("<<", $1, $3); }
    | Expr RSHIFT Expr                { $$ = make_binop(">>", $1, $3); }
    | NOT Expr %prec UNOT             { $$ = make_unaryop("~", $2); }

    | Expr ANDAND Expr                { $$ = make_binop("&&", $1, $3); }
    | Expr OROR Expr                  { $$ = make_binop("||", $1, $3); }
    | LNOT Expr                       { $$ = make_unaryop("!", $2); }

    | '-' Expr %prec UMINUS           { $$ = make_unaryop("-", $2); } 
    | '(' Expr ')'                    { $$ = $2; }
;

%%

