  /* === parser2.y === */

  %{
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>

  int yylex(void);
  void yyerror(const char *s);
  extern FILE *yyin;

  // Symbol table
  #define MAX_VARS 1024
  typedef struct {
      char *name;
      int value;
  } Variable;

  Variable symtab[MAX_VARS];
  int symcount = 0;

  int get_var(const char *name) {
      for (int i = 0; i < symcount; ++i) {
          if (strcmp(symtab[i].name, name) == 0)
              return symtab[i].value;
      }
      return 0;
  }

  void set_var(const char *name, int value) {
      for (int i = 0; i < symcount; ++i) {
          if (strcmp(symtab[i].name, name) == 0) {
              symtab[i].value = value;
              return;
          }
      }
      symtab[symcount].name = strdup(name);
      symtab[symcount].value = value;
      ++symcount;
  }
  %}

  %union {
    int ival;
    char *sval;
  }

  %token <ival> NUMBER
  %token <sval> IDENT
  %token INT RETURN IF ELSE WHILE MAIN
  %token EQ NEQ LE GE LT GT

  %left '+' '-'
  %left '*' '/' '%'
  %nonassoc EQ NEQ LE GE LT GT
  %right '='
  %nonassoc IFX
  %nonassoc ELSE

  %type <ival> expr

  %%

  program:
      function
  ;

  function:
      INT MAIN '(' ')' block
  ;

  block:
      '{' stmt_list '}'
  ;

  stmt_list:
        /* empty */
      | stmt_list stmt
  ;

  stmt:
        decl_stmt
      | expr_stmt
      | return_stmt
      | if_stmt
      | while_stmt
      | block
  ;

  decl_stmt:
        INT IDENT ';'
          { set_var($2, 0); }
      | INT IDENT '=' expr ';'
          { set_var($2, $4); }
  ;

  expr_stmt:
      expr ';'
  ;

  return_stmt:
      RETURN expr ';'
  ;

  if_stmt:
      IF '(' expr ')' stmt %prec IFX
    | IF '(' expr ')' stmt ELSE stmt
  ;

  while_stmt:
      WHILE '(' expr ')' stmt
  ;

  expr:
        expr '+' expr    { $$ = $1 + $3; }
      | expr '-' expr    { $$ = $1 - $3; }
      | expr '*' expr    { $$ = $1 * $3; }
      | expr '/' expr    { if ($3 == 0) { yyerror("division by zero"); exit(1); } else $$ = $1 / $3; }
      | expr '%' expr    { if ($3 == 0) { yyerror("modulo by zero"); exit(1); } else $$ = $1 % $3; }
      | expr EQ expr     { $$ = $1 == $3; }
      | expr NEQ expr    { $$ = $1 != $3; }
      | expr LE expr     { $$ = $1 <= $3; }
      | expr GE expr     { $$ = $1 >= $3; }
      | expr LT expr     { $$ = $1 < $3; }
      | expr GT expr     { $$ = $1 > $3; }
      | IDENT            { $$ = get_var($1); }
      | IDENT '=' expr   { set_var($1, $3); $$ = $3; }
      | '(' expr ')'     { $$ = $2; }
      | NUMBER           { $$ = $1; }
  ;

  %%

  void yyerror(const char *s) {
      fprintf(stderr, "Error: %s\n", s);
  }

  int main(int argc, char **argv) {
      if (argc > 1) {
          yyin = fopen(argv[1], "r");
          if (!yyin) {
              perror("fopen");
              return 1;
          }
      }
      yyparse();
      return 0;
  }

