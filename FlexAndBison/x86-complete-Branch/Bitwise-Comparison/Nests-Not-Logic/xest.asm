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
    mov [rbp-24], rax
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
    mov [rbp-32], rax
    mov rax, [rbp-24]
    push rax
    mov rax, [rbp-32]
    pop rbx
    or rax, rbx
    mov [rbp-40], rax
    mov rax, 0
    mov [rbp-48], rax
    mov rax, 1
    neg rax
    mov [rbp-56], rax
    mov rax, [rbp-48]
    not rax
    mov [rbp-64], rax
    mov rax, [rbp-56]
    not rax
    mov [rbp-72], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 3
    pop rbx
    and rax, rbx
    mov [rbp-80], rax
    mov rax, [rbp-16]
    push rax
    mov rax, 2
    pop rbx
    xor rax, rbx
    mov [rbp-88], rax
    mov rax, [rbp-80]
    push rax
    mov rax, [rbp-88]
    pop rbx
    or rax, rbx
    push rax
    mov rax, 1
    pop rbx
    mov rcx, rax
    mov rax, rbx
    shl rax, cl
    mov [rbp-96], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L0
    mov rax, [rbp-48]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L1
.L0:
.L1:
    mov rax, [rbp-8]
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    setne al
    movzx rax, al
    cmp rax, 0
    je .L2
    mov rax, [rbp-48]
    push rax
    mov rax, 2
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L3
.L2:
.L3:
    mov rax, [rbp-8]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    setge al
    movzx rax, al
    cmp rax, 0
    je .L4
    mov rax, [rbp-48]
    push rax
    mov rax, 4
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L5
.L4:
.L5:
    mov rax, [rbp-8]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    setle al
    movzx rax, al
    cmp rax, 0
    je .L6
    mov rax, [rbp-48]
    push rax
    mov rax, 8
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L7
.L6:
.L7:
    mov rax, [rbp-8]
    push rax
    mov rax, 1
    pop rbx
    cmp rbx, rax
    setg al
    movzx rax, al
    cmp rax, 0
    je .L8
    mov rax, [rbp-48]
    push rax
    mov rax, 16
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L9
.L8:
.L9:
    mov rax, [rbp-8]
    push rax
    mov rax, 3
    pop rbx
    cmp rbx, rax
    setl al
    movzx rax, al
    cmp rax, 0
    je .L10
    mov rax, [rbp-48]
    push rax
    mov rax, 32
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L11
.L10:
.L11:
.L12:
    mov rax, [rbp-8]
    push rax
    mov rax, 10
    pop rbx
    cmp rbx, rax
    setle al
    movzx rax, al
    cmp rax, 0
    je .L13
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
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L14
    mov rax, [rbp-8]
    push rax
    mov rax, 1
    pop rbx
    mov rcx, rax
    mov rax, rbx
    shl rax, cl
    mov [rbp-8], rax
    jmp .L15
.L14:
    mov rax, [rbp-8]
    push rax
    mov rax, 4
    pop rbx
    cmp rbx, rax
    setne al
    movzx rax, al
    cmp rax, 0
    je .L16
    mov rax, [rbp-8]
    push rax
    mov rax, 2
    pop rbx
    add rax, rbx
    mov [rbp-8], rax
    jmp .L17
.L16:
    mov rax, [rbp-8]
    push rax
    mov rax, 5
    pop rbx
    cmp rbx, rax
    setge al
    movzx rax, al
    cmp rax, 0
    je .L18
    mov rax, [rbp-16]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-16], rax
    jmp .L19
.L18:
    mov rax, [rbp-40]
    push rax
    mov rax, [rbp-8]
    pop rbx
    or rax, rbx
    mov [rbp-40], rax
.L19:
.L17:
.L15:
    jmp .L12
.L13:
    mov rax, [rbp-40]
    push rax
    mov rax, [rbp-16]
    pop rbx
    xor rax, rbx
    push rax
    mov rax, 7
    pop rbx
    and rax, rbx
    mov [rbp-104], rax
    mov rax, [rbp-104]
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L20
    mov rax, [rbp-48]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L21
.L20:
    mov rax, [rbp-104]
    push rax
    mov rax, 1
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L22
    mov rax, [rbp-48]
    push rax
    mov rax, 2
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L23
.L22:
    mov rax, [rbp-104]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L24
    mov rax, [rbp-48]
    push rax
    mov rax, 3
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L25
.L24:
    mov rax, [rbp-104]
    push rax
    mov rax, 3
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L26
    mov rax, [rbp-48]
    push rax
    mov rax, 4
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L27
.L26:
    mov rax, [rbp-104]
    push rax
    mov rax, 4
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L28
    mov rax, [rbp-48]
    push rax
    mov rax, 5
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
    jmp .L29
.L28:
    mov rax, [rbp-48]
    push rax
    mov rax, 6
    pop rbx
    add rax, rbx
    mov [rbp-48], rax
.L29:
.L27:
.L25:
.L23:
.L21:
    mov rax, [rbp-8]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-112], rax
    mov rax, [rbp-112]
    push rax
    mov rax, 2
    pop rbx
    cmp rbx, rax
    setg al
    movzx rax, al
    cmp rax, 0
    je .L30
    mov rax, [rbp-112]
    push rax
    mov rax, 10
    pop rbx
    add rax, rbx
    mov [rbp-112], rax
    jmp .L31
.L30:
.L31:
    mov rax, 0
    mov [rbp-120], rax
    mov rax, [rbp-8]
    push rax
    mov rax, 100
    pop rbx
    cmp rbx, rax
    setl al
    movzx rax, al
    cmp rax, 0
    je .L32
    mov rax, [rbp-8]
    push rax
    mov rax, 1
    pop rbx
    and rax, rbx
    push rax
    mov rax, 0
    pop rbx
    cmp rbx, rax
    setne al
    movzx rax, al
    cmp rax, 0
    je .L34
    mov rax, [rbp-8]
    push rax
    mov rax, 64
    pop rbx
    cmp rbx, rax
    sete al
    movzx rax, al
    cmp rax, 0
    je .L36
    mov rax, [rbp-120]
    push rax
    mov rax, 1
    pop rbx
    add rax, rbx
    mov [rbp-120], rax
    jmp .L37
.L36:
.L37:
    jmp .L35
.L34:
.L35:
    jmp .L33
.L32:
.L33:
    mov rax, [rbp-8]
    push rax
    mov rax, 3
    pop rbx
    and rax, rbx
    not rax
    mov [rbp-128], rax
    mov rax, [rbp-16]
    push rax
    mov rax, 1
    pop rbx
    or rax, rbx
    not rax
    mov [rbp-136], rax
    mov rax, [rbp-128]
    push rax
    mov rax, [rbp-136]
    pop rbx
    add rax, rbx
    mov [rbp-144], rax
    mov rax, 16
    neg rax
    mov [rbp-152], rax
    mov rax, [rbp-152]
    push rax
    mov rax, 2
    pop rbx
    mov rcx, rax
    mov rax, rbx
    sar rax, cl
    mov [rbp-160], rax
    mov rax, 1
    push rax
    mov rax, 2
    pop rbx
    xor rax, rbx
    push rax
    mov rax, 3
    pop rbx
    and rax, rbx
    mov [rbp-168], rax
    mov rax, 4
    push rax
    mov rax, 5
    pop rbx
    xor rax, rbx
    mov [rbp-176], rax
    mov rax, [rbp-168]
    push rax
    mov rax, [rbp-176]
    pop rbx
    or rax, rbx
    mov [rbp-184], rax
    mov rax, [rbp-112]
    push rax
    mov rax, [rbp-120]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-144]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-160]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-184]
    pop rbx
    add rax, rbx
    mov [rbp-192], rax
    mov rax, [rbp-192]
    push rax
    mov rax, 255
    pop rbx
    and rax, rbx
    push rax
    mov rax, 7
    pop rbx
    or rax, rbx
    mov [rbp-200], rax
    mov rax, [rbp-8]
    push rax
    mov rax, [rbp-16]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-40]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-48]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-56]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-64]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-72]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-96]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-112]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-120]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-144]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-160]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-184]
    pop rbx
    add rax, rbx
    push rax
    mov rax, [rbp-200]
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
