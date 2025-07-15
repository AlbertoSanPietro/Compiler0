.text
.globl __start
__start:
    daddiu $sp, $sp, -1024
    move $fp, $sp
    li $a0, 10
    sd $a0, -520($fp)
    li $a0, 2
    ld $a1, -520($fp)
    ddiv $a1, $a0
    mflo $a0
    sd $a0, -8($fp)
    ld $a0, -8($fp)
    sd $a0, -528($fp)
    li $a0, 2
    ld $a1, -528($fp)
    ddiv $a1, $a0
    mfhi $a0
    sd $a0, -16($fp)
    ld $a0, -8($fp)
    sd $a0, -536($fp)
    ld $a0, -16($fp)
    ld $a1, -536($fp)
    daddu $a0, $a1, $a0
    li $v0, 5058
    syscall
    move $a1, $a0
    li $v0, 1
    syscall
    li $v0, 93
    syscall
