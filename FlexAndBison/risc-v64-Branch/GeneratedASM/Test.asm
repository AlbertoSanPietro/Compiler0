.text
.global _start
_start:
    addi sp, sp, -16
    sd ra, 8(sp)
    sd s0, 0(sp)
    mv s0, sp
    addi sp, sp, -512
    li a0, 1
    sd a0, -8(s0)
    ld a0, -8(s0)
    li a7, 93
    ecall
.section .data
divzero_msg: .asciz "Division by zero!\n"
