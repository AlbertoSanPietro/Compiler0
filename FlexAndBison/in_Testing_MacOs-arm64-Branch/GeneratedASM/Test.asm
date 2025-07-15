.extern _exit
.text
.global _start
_start:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    sub sp, sp, #512
    mov x0, #1
    str x0, [x29, #-8]
    ldr x0, [x29, #-8]
    bl _exit
.section .data
divzero_msg: .asciz "Division by zero!\n"
