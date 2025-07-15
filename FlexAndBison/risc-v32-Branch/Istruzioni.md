## Prerequisiti

* Sistema operativo: 
    `Linux amd64`

* Pacchetti (per x86): 
    `gcc-riscv32-linux-gnu binutils-riscv32-linux-gnu qemu-user`

### Qualora i pacchetti non fossero presenti andare in fondo alla pagina

## Istruzioni

* Flex:
    `flex lexer.l`

* Bison:
    `bison -d parser.y`

* Compilazione:
	`gcc main.c riscv32codegen.c lex.yy.c parser.tab.c -o CompilerName`

* Creazione file assembly:
	`./CompilerName FileName.c > FileName.asm`

* Assembler
    `riscv32-linux-gnu-as FileName.asm -o FileName.o`

* Linking con GNU-Link
    `riscv32-linux-gnu-ld FileName.o -o ExecutableName`

* Esecuzione
    `qemu-riscv32 ./ExecutableName`

* Visualizzazione del return value
    `echo $?`



## E' possibile forzare il problema:
* Pacchetti :
    `gcc-riscv64-unknown-elf binutils-riscv64-unknown-elf`

* Assembler: 
    `riscv64-unknown-elf-as -march=rv32ima FileName.asm -o FileName.o`

* Linker:
    `riscv64-unknown-elf-ld -m elf32lriscv Filename.o -o Filename`

* Esecuzione :
    `qemu-riscv32 ./FileName`
