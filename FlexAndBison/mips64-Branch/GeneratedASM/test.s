.text
.globl __start
__start:
    daddiu $sp, $sp, -512
    move $fp, $sp
    li $a0, 2
    sd $a0, -8($fp)
.L0:
    ld $a0, -8($fp)
    sd $a0, -16($fp)
    li $a0, 10
    ld $a1, -16($fp)
    slt $a0, $a1, $a0
    beqz $a0, .L1
    ld $a0, -8($fp)
    sd $a0, -16($fp)
    li $a0, 2
    ld $a1, -16($fp)
    ddiv $t0, $a1, $a0
    dmul $t0, $t0, $a0
    dsubu $a0, $a1, $t0
    sd $a0, -16($fp)
    li $a0, 0
    ld $a1, -16($fp)
    seq $a0, $a1, $a0
    beqz $a0, .L2
    ld $a0, -8($fp)
    sd $a0, -16($fp)
    li $a0, 1
    ld $a1, -16($fp)
    daddu $a0, $a1, $a0
    sd $a0, -8($fp)
    b .L3
.L2:
    ld $a0, -8($fp)
    sd $a0, -16($fp)
    li $a0, 2
    ld $a1, -16($fp)
    daddu $a0, $a1, $a0
    sd $a0, -8($fp)
.L3:
    b .L0
.L1:
    ld $a0, -8($fp)
    li $v0, 5058
    syscall
    move $a1, $a0
    li $v0, 1
    syscall
    li $v0, 93
    syscall
