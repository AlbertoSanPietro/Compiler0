/* text concordance */
%option noyywrap nodefault yylineno case-insensitive
/* the symbol table */ 
%{
#include <stdio.h>

struct symbol {
	char *name;
	struct ref *reflist;
};

struct ref {
	struct ref *next;
	char *filename;
	int flags;
	int lineno;
};

//Simple symtab of fixed size
#define NHASH 9997
struct symbol symtab[NHASH];

struct symbol *lookup(char *);
void addref(int char *, char *, int);

char *curfilename;


%}

/*Rules and skip common words*/

%%



a |
an |
and |
are |
as |
at |
be | 
but |
for |
in |
is |
it |
of |
on |
or |
that |
the |
this |
to  /*ignore*/

[a-z]+(\'(s|t))? { addref(yylineno, curfilename, yytext, 0); }
.|\n /*Ignore everything else*/

%%

int main(int argc, char **argv) {
	int i;

	if (argc<2) {
		//read stdin
		curfilename = "(stdin)";
		yylineno = 1;
		yylex();
	} else {
			for (i = 1; i < argc; i++) {
				FILE *f= fopen(argv[i], "r");

				if (!f) {
					perror(argv[1]);
					return (1);
				}
				curfilename = argv[i]; //for addref

				yyrestart(f);
				yylineno= 1;
				yylex();
				fclose(f);
			}

			printrefs();
	}
}
