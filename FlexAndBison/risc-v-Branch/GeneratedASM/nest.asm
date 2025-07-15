.text
.global _start
_start:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd s0, 0(sp)
    mv s0, sp
    addi sp, sp, -512
    li a0, 2
    sd a0, -8(s0)
    li a0, 5
    neg a0, a0
    sd a0, -16(s0)
.L0:
    ld a0, -8(s0)
    addi sp, sp, -8
    sd a0, 0(sp)
    li a0, 10
    ld a1, 0(sp)
    addi sp, sp, 8
    sltu a0, a1, a0
    beqz a0, .L1
    ld a0, -8(s0)
    addi sp, sp, -8
    sd a0, 0(sp)
    li a0, 2
    ld a1, 0(sp)
    addi sp, sp, 8
    remu a0, a1, a0
    addi sp, sp, -8
    sd a0, 0(sp)
    li a0, 0
    ld a1, 0(sp)
    addi sp, sp, 8
    sub a0, a1, a0
    seqz a0, a0
    beqz a0, .L2
    ld a0, -8(s0)
    addi sp, sp, -8
    sd a0, 0(sp)
    li a0, 1
    ld a1, 0(sp)
    addi sp, sp, 8
    add a0, a1, a0
    sd a0, -8(s0)
    j .L3
.L2:
    ld a0, -8(s0)
    addi sp, sp, -8
    sd a0, 0(sp)
    li a0, 2
    ld a1, 0(sp)
    addi sp, sp, 8
    add a0, a1, a0
    sd a0, -8(s0)
.L3:
    j .L0
.L1:
    ld a0, -8(s0)
    addi sp, sp, -8
    sd a0, 0(sp)
    ld a0, -16(s0)
    ld a1, 0(sp)
    addi sp, sp, 8
    add a0, a1, a0
    li a7, 93
    ecall
.section .data
divzero_msg: .asciz "Division by zero!\n"
