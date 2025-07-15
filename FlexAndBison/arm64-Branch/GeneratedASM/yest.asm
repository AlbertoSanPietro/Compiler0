.text
.global _start
_start:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    sub sp, sp, #512
    mov x0, #0
    str x0, [sp, #-16]!
    mov x0, #1
    ldr x1, [sp], #16
    sub x0, x1, x0
    str x0, [x29, #-8]
    ldr x0, [x29, #-8]
    mov x8, #93
    svc #0
.section .data
divzero_msg: .asciz "Division by zero!\n"
