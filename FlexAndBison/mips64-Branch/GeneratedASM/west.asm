.text
.globl __start
__start:
    daddiu $sp, $sp, -1024
    move $fp, $sp
    li $a0, 0
    li $v0, 5058
    syscall
    move $a1, $a0
    li $v0, 1
    syscall
    li $v0, 93
    syscall
