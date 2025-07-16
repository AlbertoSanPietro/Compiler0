test:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov [rbp-8], rdi
    mov [rbp-16], rsi
    mov [rbp-24], rdx
    mov rax, [rbp-24]
    push rax
    mov rax, [rbp-16]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-8]
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-32], rax
    mov rax, 0
    leave
    ret
section .text
global _start
_start:
    call main
    mov rdi, rax
    mov rax, 60
    syscall
main:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov rax, 2
    mov [rbp-40], rax
    mov rax, [rbp-40]
    push rax
    mov rax, 1
    pop rbx
    mov rcx, rax
    mov rax, rbx
    sar rax, cl
    mov [rbp-48], rax
    mov rax, 5
    push rax
    mov rax, 3
    pop rbx
    and rbx, rax
    mov rax, rbx
    push rax
    mov rax, 1
    push rax
    mov rax, 7
    push rax
    mov rax, 2
    pop rbx
    mov rcx, rax
    mov rax, rbx
    shl rax, cl
    pop rbx
    xor rbx, rax
    mov rax, rbx
    pop rbx
    or rbx, rax
    mov rax, rbx
    mov [rbp-56], rax
    mov rax, 0
    mov [rbp-24], rax
    mov rax, 1
    neg rax
    mov [rbp-16], rax
    mov rax, [rbp-24]
    not rax
    mov [rbp-8], rax
    mov rax, [rbp-16]
    not rax
    mov [rbp-32], rax
    mov rax, [rbp-40]
    push rax
    mov rax, 3
    pop rbx
    and rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-48]
    push rax
    mov rax, 2
    pop rbx
    xor rbx, rax
    mov rax, rbx
    pop rbx
    or rbx, rax
    mov rax, rbx
    push rax
    mov rax, 1
    pop rbx
    mov rcx, rax
    mov rax, rbx
    shl rax, cl
    mov [rbp-64], rax
    mov rax, [rbp-40]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L0
    mov rax, [rbp-24]
    push rax
    mov rax, 1
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L1
.L0:
.L1:
    mov rax, [rbp-40]
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    setne al
    movzx rax, al
    cmp rax, 0
    je .L2
    mov rax, [rbp-24]
    push rax
    mov rax, 2
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L3
.L2:
.L3:
    mov rax, [rbp-40]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    setge al
    movzx rax, al
    cmp rax, 0
    je .L4
    mov rax, [rbp-24]
    push rax
    mov rax, 4
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L5
.L4:
.L5:
    mov rax, [rbp-40]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    setle al
    movzx rax, al
    cmp rax, 0
    je .L6
    mov rax, [rbp-24]
    push rax
    mov rax, 8
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L7
.L6:
.L7:
    mov rax, [rbp-40]
    push rax
    mov rax, 1
    pop rbx
    cmp rbx, rax
    setg al
    movzx rax, al
    cmp rax, 0
    je .L8
    mov rax, [rbp-24]
    push rax
    mov rax, 16
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L9
.L8:
.L9:
    mov rax, [rbp-40]
    push rax
    mov rax, 3
    pop rbx
    cmp rbx, rax
    setl al
    movzx rax, al
    cmp rax, 0
    je .L10
    mov rax, [rbp-24]
    push rax
    mov rax, 32
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L11
.L10:
.L11:
.L12:
    mov rax, [rbp-40]
    push rax
    mov rax, 10
    pop rbx
    cmp rbx, rax
    setle al
    movzx rax, al
    cmp rax, 0
    je .L13
    mov rax, [rbp-40]
    push rax
    mov rax, 2
    pop rbx
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L14
    mov rax, [rbp-40]
    push rax
    mov rax, 1
    pop rbx
    mov rcx, rax
    mov rax, rbx
    shl rax, cl
    mov [rbp-40], rax
    jmp .L15
.L14:
    mov rax, [rbp-40]
    push rax
    mov rax, 4
    pop rbx
    cmp rbx, rax
    setne al
    movzx rax, al
    cmp rax, 0
    je .L16
    mov rax, [rbp-40]
    push rax
    mov rax, 2
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-40], rax
    mov rax, [rbp-40]
    push rax
    mov rax, 4
    pop rbx
    imul rbx, rax
    mov rax, rbx
    mov [rbp-40], rax
    jmp .L17
.L16:
    mov rax, [rbp-40]
    push rax
    mov rax, 5
    pop rbx
    cmp rbx, rax
    setge al
    movzx rax, al
    cmp rax, 0
    je .L18
    mov rax, [rbp-48]
    push rax
    mov rax, 1
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-48], rax
    jmp .L19
.L18:
    mov rax, [rbp-56]
    push rax
    mov rax, [rbp-40]
    pop rbx
    or rbx, rax
    mov rax, rbx
    mov [rbp-56], rax
.L19:
.L17:
.L15:
    jmp .L12
.L13:
    mov rax, [rbp-56]
    push rax
    mov rax, [rbp-48]
    pop rbx
    xor rbx, rax
    mov rax, rbx
    push rax
    mov rax, 7
    pop rbx
    and rbx, rax
    mov rax, rbx
    mov [rbp-72], rax
    mov rax, [rbp-72]
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L20
    mov rax, [rbp-24]
    push rax
    mov rax, 1
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L21
.L20:
    mov rax, [rbp-72]
    push rax
    mov rax, 1
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L22
    mov rax, [rbp-24]
    push rax
    mov rax, 2
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L23
.L22:
    mov rax, [rbp-72]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L24
    mov rax, [rbp-24]
    push rax
    mov rax, 3
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L25
.L24:
    mov rax, [rbp-72]
    push rax
    mov rax, 3
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L26
    mov rax, [rbp-24]
    push rax
    mov rax, 4
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L27
.L26:
    mov rax, [rbp-72]
    push rax
    mov rax, 4
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L28
    mov rax, [rbp-24]
    push rax
    mov rax, 5
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    jmp .L29
.L28:
    mov rax, [rbp-24]
    push rax
    mov rax, 6
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
.L29:
.L27:
.L25:
.L23:
.L21:
    mov rax, [rbp-40]
    push rax
    mov rax, [rbp-48]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-56]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-24]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-16]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-8]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-32]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    mov rax, [rbp-64]
    pop rbx
    add rbx, rax
    mov rax, rbx
    leave
    ret
.divzero:
    mov rax, 1
    mov rdi, 1
    mov rsi, divzero_msg
    mov rdx, divzero_len
    syscall
    mov rdi, 1
    mov rax, 60
    syscall
section .data
divzero_msg: db "Division by zero!", 10
divzero_len: equ $ - divzero_msg
