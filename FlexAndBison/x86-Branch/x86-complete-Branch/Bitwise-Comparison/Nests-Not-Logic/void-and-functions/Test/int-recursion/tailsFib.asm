fib_tail:
    push rbp
    mov rbp, rsp
    sub rsp, 512
    mov [rbp-8], rdi
    mov [rbp-16], rsi
    mov [rbp-24], rdx
    mov rax, [rbp-24]
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L0
    mov rax, [rbp-16]
    leave
    ret
    jmp .L1
.L0:
.L1:
    mov rax, [rbp-24]
    push rax
    mov rax, 1
    pop rbx
    mov rcx, rax
    mov rax, rbx
    sub rax, rcx
    push rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    push rax
    mov rax, [rbp-8]
    pop rbx
    add rbx, rax
    mov rax, rbx
    push rax
    pop rdi
    pop rsi
    pop rdx
    call fib_tail
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
    push rax
    mov rax, 0
    push rax
    mov rax, 1
    push rax
    pop rdi
    pop rsi
    pop rdx
    call fib_tail
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
