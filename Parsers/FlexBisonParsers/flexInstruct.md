### How to run simple flex programs

# use flex to produce the yy.c file
`flex namefile.l`
compile with any C/C++ compiler:
`gcc lex.yy.c`
`cc lex.yy.c`
`clang lex.yy.c`

## Remember to check if the flex file reads from stdin or from a file!
By default it's all stdin.
To finish the program and get the results:
Linux:
`Ctrl+D` or `^D`
Windows:
`Ctrl+Z` or `^Z`

