section .text
global _start
_start:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov rax, 1
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
