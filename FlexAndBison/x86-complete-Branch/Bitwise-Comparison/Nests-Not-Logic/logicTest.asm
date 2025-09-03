section .text
global _start
_start:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov rax, 0
    mov [rbp-8], rax
    mov rax, 1
    mov [rbp-16], rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    pop rbx
    cmp rbx, 0
    je .L0
    cmp rax, 0
    je .L0
    mov rax, 1
    jmp .L1
.L0:
    mov rax, 0
.L1:
    mov [rbp-24], rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    pop rbx
    cmp rbx, 0
    jne .L2
    cmp rax, 0
    jne .L2
    mov rax, 0
    jmp .L3
.L2:
    mov rax, 1
.L3:
    mov [rbp-32], rax
    mov rax, [rbp-8]
    cmp rax, 0
    sete al
    movzx rax, al
    mov [rbp-40], rax
    mov rax, [rbp-24]
    push rax
    mov rax, [rbp-32]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-40]
    pop rbx
    add rax, rbx
    mov rdi, rax
    mov rax, 60
    syscall
    mov rdi, 0
    mov rax, 60
    syscall
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
