.text
.globl __start
__start:
    daddiu $sp, $sp, -1024
    move $fp, $sp
    li $a0, 0
    sd $a0, -520($fp)
    li $a0, 1
    ld $a1, -520($fp)
    dsubu $a0, $a1, $a0
    sd $a0, -8($fp)
    ld $a0, -8($fp)
    li $v0, 5058
    syscall
    move $a1, $a0
    li $v0, 1
    syscall
    li $v0, 93
    syscall
