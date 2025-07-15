## README

```
brew install flex bison
brew install aarch64-none-elf-binutils  # for assembler/linker
```
## Then

```
bison -d parser.y
flex lexer.l
```

## Compile with:

```
gcc lex.yy.c parser.tab.c main.c macos_codegen.c -o Compiler
```
 
## Run the compiler:

`./Compiler test.c > test.s`

## Assemble :
`clang -arch arm64 test.s -o test`

## Run the file:
`./test`

## Check if it ran correctly:
`echo $?`

You should see the return value of the program. 
Here is a cheatsheet for it:
```
test.c == 11
Dest.c == 6 
Test.c == 1
West.c == 0
Zest.c == 7
```
Rest.c contains a syntax error on line 1 and will NOT compile

