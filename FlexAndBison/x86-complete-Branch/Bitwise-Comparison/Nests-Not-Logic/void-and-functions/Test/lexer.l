%{
#include "parser.tab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
%}

%%

"int"           { return INT; }
"main"          { return MAIN; }
"if"            { return IF; }
"else"          { return ELSE; }
"while"         { return WHILE; }
"return"        { return RETURN; }

"void"          { return VOID; }


"=="            { return EQ; }
"!="            { return NEQ; }
"<="            { return LE; }
">="            { return GE; }
"<"             { return LT; }
">"             { return GT; }
"&&"            { return ANDAND; }
"||"            { return OROR; }
"!"             { return LNOT; }



"<<"            { return LSHIFT; }
">>"            { return RSHIFT; }
"&"             { return AND; }
"|"             { return OR; }
"^"             { return XOR; }
"~"             { return NOT; }


"%"             { return '%'; }
"="             { return '='; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }

","             { return ','; }
";"             { return ';'; }
"("             { return '('; }
")"             { return ')'; }
"{"             { return '{'; }
"}"             { return '}'; }

[0-9]+           { yylval.ival = atoi(yytext); return NUMBER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.sval = strdup(yytext); return IDENT; }

"//".*                 { /* skip single-line comment */ }
"/*"([^*]|\*+[^*/])*\*+"/" { /* skip multi-line comment */ }

[ \t\r\n]+             { /* skip whitespace */ }

.                {
                    fprintf(stderr, "Unexpected character: %s\n", yytext);
                    exit(1);
                }

%%

int yywrap(void) {
    return 1;
}

