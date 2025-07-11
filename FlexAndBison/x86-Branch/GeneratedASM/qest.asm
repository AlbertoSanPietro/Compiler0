section .text
global _start
_start:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov rax, 5
    mov [rbp-8], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-16], rax
    mov rax, 0
    mov [rbp-24], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 5
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L0
    mov rax, [rbp-16]
    mov [rbp-24], rax
    jmp .L1
.L0:
.L1:
    mov rax, [rbp-24]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-8], rax
    mov rax, [rbp-8]
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
