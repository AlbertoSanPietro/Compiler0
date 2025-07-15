.text
.global _start
_start:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    mv s0, sp
    addi sp, sp, -512
    li a0, 5
    sw a0, -4(s0)
    lw a0, -4(s0)
    addi sp, sp, -4
    sw a0, 0(sp)
    li a0, 2
    lw a1, 0(sp)
    addi sp, sp, 4
    remu a0, a1, a0
    addi sp, sp, -4
    sw a0, 0(sp)
    li a0, 0
    lw a1, 0(sp)
    addi sp, sp, 4
    sub a0, a1, a0
    seqz a0, a0
    beqz a0, .L0
    lw a0, -4(s0)
    addi sp, sp, -4
    sw a0, 0(sp)
    li a0, 1
    lw a1, 0(sp)
    addi sp, sp, 4
    add a0, a1, a0
    sw a0, -4(s0)
    j .L1
.L0:
    lw a0, -4(s0)
    addi sp, sp, -4
    sw a0, 0(sp)
    li a0, 2
    lw a1, 0(sp)
    addi sp, sp, 4
    add a0, a1, a0
    sw a0, -4(s0)
.L1:
    lw a0, -4(s0)
    li a7, 93
    ecall
.section .data
divzero_msg: .asciz "Division by zero!\n"
