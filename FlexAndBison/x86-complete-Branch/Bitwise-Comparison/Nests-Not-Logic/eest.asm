section .text
global _start
_start:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov rax, 2
    mov [rbp-8], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 1
    pop rbx
    mov rcx, rax
    mov rax, rbx
    sar rax, cl
    mov [rbp-16], rax
    mov rax, 5
    push rax
    mov rax, 3
    pop rbx
    and rax, rbx
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
    xor rax, rbx
    pop rbx
    or rax, rbx
    mov [rbp-24], rax
    mov rax, 0
    mov [rbp-32], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L0
    mov rax, [rbp-32]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-32], rax
    jmp .L1
.L0:
.L1:
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-24]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-32]
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
