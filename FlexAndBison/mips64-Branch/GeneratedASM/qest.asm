.text
.globl __start
__start:
    daddiu $sp, $sp, -1024
    move $fp, $sp
    li $a0, 5
    sd $a0, -8($fp)
    ld $a0, -8($fp)
    sd $a0, -520($fp)
    li $a0, 1
    ld $a1, -520($fp)
    daddu $a0, $a1, $a0
    sd $a0, -16($fp)
    li $a0, 0
    sd $a0, -24($fp)
    ld $a0, -8($fp)
    sd $a0, -528($fp)
    li $a0, 5
    ld $a1, -528($fp)
    seq $a0, $a1, $a0
    beqz $a0, .L0
    ld $a0, -16($fp)
    sd $a0, -24($fp)
    b .L1
.L0:
.L1:
    ld $a0, -24($fp)
    sd $a0, -536($fp)
    li $a0, 1
    ld $a1, -536($fp)
    daddu $a0, $a1, $a0
    sd $a0, -8($fp)
    ld $a0, -8($fp)
    li $v0, 5058
    syscall
    move $a1, $a0
    li $v0, 1
    syscall
    li $v0, 93
    syscall
