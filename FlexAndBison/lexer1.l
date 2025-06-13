%{
#include "parser.tab.h"   // Bison-generated header for token definitions
#include <stdlib.h>
#include <string.h>

//int yylval;               // If you're using union in Bison, adjust accordingly
char* strdup(const char*); // Declare strdup if needed
%}

%%

"int"           { return INT; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"return"        { return RETURN; }

"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }

"="             { return '='; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"%"             { return '%'; }

";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }

[0-9]+          {
                  yylval = atoi(yytext);
                  return NUMBER;
                }

[a-zA-Z_][a-zA-Z0-9_]* {
                  yylval = (int)strdup(yytext);  // Or use a union if needed
                  return IDENT;
                }

[ \t\r\n]+      { /* Skip whitespace */ }

.               {
                  fprintf(stderr, "Unexpected character: %s\n", yytext);
                  exit(1);
                }

%%

int yywrap() {
  return 1;
}

