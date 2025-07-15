.text
.globl __start
__start:
    daddiu $sp, $sp, -1024
    move $fp, $sp
    li $a0, 2
    sd $a0, -8($fp)
    li $a0, 5
    dneg $a0, $a0
    sd $a0, -16($fp)
.L0:
    ld $a0, -8($fp)
    sd $a0, -520($fp)
    li $a0, 10
    ld $a1, -520($fp)
    slt $a0, $a1, $a0
    beqz $a0, .L1
    ld $a0, -8($fp)
    sd $a0, -528($fp)
    li $a0, 2
    ld $a1, -528($fp)
    ddiv $a1, $a0
    mfhi $a0
    sd $a0, -536($fp)
    li $a0, 0
    ld $a1, -536($fp)
    seq $a0, $a1, $a0
    beqz $a0, .L2
    ld $a0, -8($fp)
    sd $a0, -544($fp)
    li $a0, 1
    ld $a1, -544($fp)
    daddu $a0, $a1, $a0
    sd $a0, -8($fp)
    b .L3
.L2:
    ld $a0, -8($fp)
    sd $a0, -552($fp)
    li $a0, 2
    ld $a1, -552($fp)
    daddu $a0, $a1, $a0
    sd $a0, -8($fp)
.L3:
    b .L0
.L1:
    ld $a0, -8($fp)
    sd $a0, -560($fp)
    ld $a0, -16($fp)
    ld $a1, -560($fp)
    daddu $a0, $a1, $a0
    li $v0, 5058
    syscall
    move $a1, $a0
    li $v0, 1
    syscall
    li $v0, 93
    syscall
