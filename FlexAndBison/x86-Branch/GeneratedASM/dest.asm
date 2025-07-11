section .text
global _start
_start:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov rax, 10
    push rax
    mov rax, 2
    pop rbx
    cmp rax, 0
    je .divzero
    mov rcx, rax
    mov rax, rbx
    cqo
    idiv rcx
    mov [rbp-8], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 2
    pop rbx
    cmp rax, 0
    je .divzero
    mov rcx, rax
    mov rax, rbx
    cqo
    idiv rcx
    mov rax, rdx
    mov [rbp-16], rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
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
