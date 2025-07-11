# How to run simple Bison/Yacc programs

### Use bison to produce the .tab.c and .tab.h files
`bison -d fileName.l`

### Compilation is CANNOT be done without a flex file.
`gcc lex.yy.c fileName.tab.c -lfl`
`cc lex.yy.c fileName.tab.c -lfl`
`clang lex.yy.c fileName.tab.c -lfl`



