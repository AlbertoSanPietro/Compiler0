## Prerequisiti

* Sistema operativo: 
    `Linux amd64`

* Pacchetti (per x86): 
    `qemu-user qemu-user-static gcc-aarch64-linux-gnu`


## Istruzioni

* Flex:
    `flex lexer.l`

* Bison:
    `bison -d parser.y`

* Compilazione:
	`gcc main.c arm64codegen.c lex.yy.c parser.tab.c -o CompilerName`

* Creazione file assembly:
	`./CompilerName FileName.c > FileName.asm`

* Assembler
    `aarch64-linux-gnu-as FileName.asm -o FileName.o`

* Linking con GNU-Link
    `aarch64-linux-gnu-ld FileName.o -o ExecutableName`

* Esecuzione
    `qemu-aarch64 ./ExecutableName`

* Visualizzazione del return value
    `echo $?`


