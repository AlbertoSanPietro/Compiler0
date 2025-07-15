.text
.global _start
_start:
    addi sp, sp, -8
    sw ra, 4(sp)
    sw s0, 0(sp)
    mv s0, sp
    addi sp, sp, -512
    li a0, 1
    sw a0, -4(s0)
    lw a0, -4(s0)
    li a7, 93
    ecall
.section .data
divzero_msg: .asciz "Division by zero!\n"
