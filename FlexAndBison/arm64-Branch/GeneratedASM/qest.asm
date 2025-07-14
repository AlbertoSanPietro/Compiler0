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
    mov x0, #1
    ldr x1, [sp], #16
    add x0, x1, x0
    str x0, [x29, #-16]
    mov x0, #0
    str x0, [x29, #-24]
    ldr x0, [x29, #-8]
    str x0, [sp, #-16]!
    mov x0, #5
    ldr x1, [sp], #16
    cmp x1, x0
    cset x0, eq
    cbz x0, .L0
    ldr x0, [x29, #-16]
    str x0, [x29, #-24]
    b .L1
.L0:
.L1:
    ldr x0, [x29, #-24]
    str x0, [sp, #-16]!
    mov x0, #1
    ldr x1, [sp], #16
    add x0, x1, x0
    str x0, [x29, #-8]
    ldr x0, [x29, #-8]
    mov x8, #93
    svc #0
.section .data
divzero_msg: .asciz "Division by zero!\n"
