#include <stdio.h>
#include <stdlib.h>

extern FILE* yyin;
extern int yyparse(void);

int main(int argc, char** argv) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s file.c > out.asm\n", argv[0]);
        return 1;
    }

    FILE* input = fopen(argv[1], "r");
    if (!input) {
        perror("fopen");
        return 1;
    }

    yyin = input;
    yyparse();
    fclose(input);
    return 0;
}

