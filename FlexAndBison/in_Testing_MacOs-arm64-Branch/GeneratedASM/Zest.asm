.extern _exit
.text
.global _start
_start:
    stp x29, x30, [sp, #-16]!
    mov x29, sp
    sub sp, sp, #512
    mov x0, #5
    str x0, [x29, #-8]
    ldr x0, [x29, #-8]
    str x0, [sp, #-16]!
    mov x0, #2
    ldr x1, [sp], #16
    udiv x2, x1, x0
    msub x0, x2, x0, x1
    str x0, [sp, #-16]!
    mov x0, #0
    ldr x1, [sp], #16
    cmp x1, x0
    cset x0, eq
    cbz x0, .L0
    ldr x0, [x29, #-8]
    str x0, [sp, #-16]!
    mov x0, #1
    ldr x1, [sp], #16
    add x0, x1, x0
    str x0, [x29, #-8]
    b .L1
.L0:
    ldr x0, [x29, #-8]
    str x0, [sp, #-16]!
    mov x0, #2
    ldr x1, [sp], #16
    add x0, x1, x0
    str x0, [x29, #-8]
.L1:
    ldr x0, [x29, #-8]
    bl _exit
.section .data
divzero_msg: .asciz "Division by zero!\n"
