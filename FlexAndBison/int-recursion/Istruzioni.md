## Istruzioni

* Flex:
    `flex lexer.l`

* Bison:
    `bison -d parser.y`

* Compilazione:
	`gcc main.c codegen.c lex.yy.c parser.tab.c -o CompilerName`

* Creazione file assembly:
	`./CompilerName FileName.c > FileName.asm`

* Assembler
    `nasm -f elf64 FileName.asm -o FileName.o`

* Linking con GNU-Link
    `ld FileName.o -o ExecutableName`

* Esecuzione
    `./ExecutableName`

* Visualizzazione del return value
    `echo $?`



