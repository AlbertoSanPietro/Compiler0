## Prerequisiti

* Sistema operativo: 
    `Linux amd64`

* Pacchetti (per x86): 
    `gcc-riscv64-linux-gnu binutils-riscv64-linux-gnu qemu-user`


## Istruzioni

* Flex:
    `flex lexer.l`

* Bison:
    `bison -d parser.y`

* Compilazione:
	`gcc main.c riscv64codegen.c lex.yy.c parser.tab.c -o CompilerName`

* Creazione file assembly:
	`./CompilerName FileName.c > FileName.asm`

* Assembler
    `riscv64-linux-gnu-as FileName.asm -o FileName.o`
potrebbe cambiare per riscv
* Linking con GNU-Link
    `riscv64-linux-gnu-ld FileName.o -o ExecutableName`
potrebbe cambiare per riscv
* Esecuzione
    `qemu-riscv64 ./ExecutableName`
potrebbe cambiare per riscv
* Visualizzazione del return value
    `echo $?`


