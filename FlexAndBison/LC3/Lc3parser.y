/* parser.y – Bison grammar with LC-3 code emission */

%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Symbol table: map variable names to LC-3 labels */
#define MAX_VARS 256
static char *var_names[MAX_VARS];
static int var_count = 0;

/* Helper: get or add a variable label */
const char* get_var_label(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(var_names[i], name) == 0) {
            return var_names[i];
        }
    }
    /* new variable */
    if (var_count >= MAX_VARS) {
        fprintf(stderr, "Too many variables!\n");
        exit(1);
    }
    var_names[var_count] = strdup(name);
    return var_names[var_count++];
}

/* Label counter for unique branch labels */
static int label_counter = 0;
char* new_label() {
    static char buf[32];
    snprintf(buf, sizeof(buf), "L%d", label_counter++);
    return strdup(buf);
}

/* Emit a line of LC-3 code */
void emit(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    va_end(args);
    printf("\n");
}

int yylex(void);
void yyerror(const char *s) {
    fprintf(stderr, "Parse error: %s\n", s);
    exit(1);
}

%}

/* ————————————————————————— Tokens and precedence ————————————————————————— */
%union {
    int ival;
    char *sval;
}

%token <ival> NUMBER
%token <sval> IDENTIFIER
%token INT RETURN IF ELSE WHILE
%token EQ NE LE GE

%left '='
%nonassoc EQ NE '<' '>' LE GE
%left '+' '-'
%left '*' '/' '%'
%nonassoc IFX
%nonassoc ELSE

%start program

%%

program:
      /* prologue */
      { emit(".ORIG x3000");
        emit("JSR MAIN");
        emit("HALT"); }
    function_definition
      {
        /* epilogue */
        emit(".END");
      }
;

function_definition:
      INT IDENTIFIER '(' ')' compound_statement
      {
        if (strcmp($2, "main") != 0) {
            fprintf(stderr, "Only main is allowed!\n");
            exit(1);
        }
        /* Entry point label */
        emit("MAIN:");
      }
;

compound_statement:
      '{' stmt_list '}'
;

stmt_list:
      /* empty */
    | stmt_list statement
;

statement:
      declaration
    | assignment
    | if_statement
    | while_statement
    | return_statement
    | ';'
;

declaration:
      INT IDENTIFIER opt_init ';'
      {
        const char *lbl = get_var_label($2);
        if ($3) {
            /* initialize */
            emit("; init %s", lbl);
            emit("LD R1, =%s", lbl);
            emit("ADD R0, R1, #0");
            emit("LEA R1, =%d", $3);
            emit("ADD R0, R0, R1");
            emit("ST R0, %s", lbl);
        } else {
            /* default zero */
            emit("; reserve %s", lbl);
            /* .BLKW later */
        }
      }
;

opt_init:
      /* empty */ { $$ = 0; }
    | '=' expression { $$ = $2; }
;

assignment:
      IDENTIFIER '=' expression ';'
      {
        const char *lbl = get_var_label($1);
        /* result in R0 */
        emit("ST R0, %s", lbl);
      }
;

if_statement:
      IF '(' expression ')' statement %prec IFX
      {
        /* no else: if zero, skip */
        char *L1 = new_label();
        emit("BRz %s", L1);
        /* then-stmt emitted */
        emit("%s:", L1);
      }
    | IF '(' expression ')' statement ELSE statement
      {
        char *L1 = new_label();
        char *L2 = new_label();
        /* cond in R0 */
        emit("BRz %s", L1);
        /* then */
        /* jump past else */
        emit("BR %s", L2);
        emit("%s:", L1);
        /* else-stmt */
        emit("%s:", L2);
      }
;

while_statement:
      WHILE '(' expression ')' statement
      {
        char *L1 = new_label();
        char *L2 = new_label();
        emit("%s:", L1);
        /* cond in R0 */
        emit("BRz %s", L2);
        /* body */
        emit("BR %s", L1);
        emit("%s:", L2);
      }
;

return_statement:
      RETURN expression ';'
      {
        /* result in R0, RET */
        emit("RET");
      }
;

expression:
      expression '+' expression
        { emit("ADD R0, R1, R2"); }
    | expression '-' expression
        { emit("SUB R0, R1, R2"); }
    | expression '*' expression
        { emit("MUL R0, R1, R2  ; pseudo-op"); }
    | expression '/' expression
        { emit("DIV R0, R1, R2  ; pseudo-op"); }
    | expression '%' expression
        { emit("MOD R0, R1, R2  ; pseudo-op"); }
    | expression EQ expression
        { emit("? EQ not implemented"); }
    | expression NE expression
        { emit("? NE not implemented"); }
    | expression '<' expression
        { emit("? LT not implemented"); }
    | expression '>' expression
        { emit("? GT not implemented"); }
    | expression LE expression
    | expression GE expression
    | '(' expression ')'
    | IDENTIFIER
        {
            const char *lbl = get_var_label($1);
            emit("LD R0, %s", lbl);
        }
    | NUMBER
        {
            emit("LD R0, =%d", $1);
        }
;

%%

int main(void) {
    return yyparse();
}

