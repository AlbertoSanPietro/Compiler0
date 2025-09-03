test:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov [rbp-8], rdi
    mov [rbp-16], rsi
    mov rax, [rbp-16]
    push rax
    mov rax, [rbp-8]
    pop rbx
    add rbx, rax
    mov rax, rbx
    mov [rbp-24], rax
    xor rax, rax
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
    mov rax, 10
    mov [rbp-8], rax
    mov rax, 20
    mov [rbp-16], rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    push rax
    pop rdi
    pop rsi
    call test
    mov rax, 0
    leave
    ret
.divzero:
    mov rax, 1
    mov rdi, 1
    lea rsi, [rel divzero_msg]
    mov rdx, divzero_len
    syscall
    mov rax, 60
    xor rdi, rdi
    syscall
section .data
    divzero_msg: db "Division by zero!\n"
    divzero_len: equ $ - divzero_msg
