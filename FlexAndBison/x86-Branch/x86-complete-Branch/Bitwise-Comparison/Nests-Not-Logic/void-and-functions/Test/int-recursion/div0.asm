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
    mov rax, 0
    mov [rbp-16], rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    pop rbx
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
