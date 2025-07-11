## How to compile and run (Linux x86_64):

`bison -d "parserName.y"` 
(eg `bison -d parser2.y`)

This should produce two files: parserName.tab.h and parserName.tab.c

`flex "lexername.l"` 
(eg `flex lexer2.l`)
	This should produce one file: `lex.yy.c`

Then the files must be compiled, there are two ways to do this. 
If you have no idea what you are doing, please check the documentation for GCC flags or use man gcc.

`gcc -o filename lex.yy.c parserName.tab.c -lfl`

The "-lfl" links to the flex library (libfl.a) and can be useful. I would say this is the preferred way.
The "-o" flag gives a name to the output file.
The other two are simply the names of the two files.

The second way is:

`gcc lex.yy.c parserName.tab.c -o compiler`

This omits the -lfl flag. It should work anyway. GCC flags can often be given in any order, and so can the files.

This is only meant to run on Linux, as of now. 



