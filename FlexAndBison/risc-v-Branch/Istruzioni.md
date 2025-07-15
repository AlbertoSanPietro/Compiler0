## Prerequisiti

* Sistema operativo: 
    `Linux amd64`

* Pacchetti (per x86): 
    `qemu-user qemu-user-static gcc-aarch64-linux-gnu`
    Potrebbe cambiare per riscv, cerca online


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
potrebbe cambiare per riscv
* Linking con GNU-Link
    `aarch64-linux-gnu-ld FileName.o -o ExecutableName`
potrebbe cambiare per riscv
* Esecuzione
    `qemu-aarch64 ./ExecutableName`
potrebbe cambiare per riscv
* Visualizzazione del return value
    `echo $?`


