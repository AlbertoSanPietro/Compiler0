	.file	"FPTest.c"
	.text
	.globl	test
	.type	test, @function
test:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -20(%rbp)
	movl	%esi, -24(%rbp)
	movl	%edx, -28(%rbp)
	movl	-20(%rbp), %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	addl	%edx, %eax
	movl	%eax, -4(%rbp)
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	test, .-test
	.globl	fib_local
	.type	fib_local, @function
fib_local:
.LFB1:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	cmpl	$1, -36(%rbp)
	jg	.L4
	movl	-36(%rbp), %eax
	movl	%eax, -20(%rbp)
	jmp	.L5
.L4:
	movl	-36(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	fib_local
	movl	%eax, %ebx
	movl	-36(%rbp), %eax
	subl	$2, %eax
	movl	%eax, %edi
	call	fib_local
	addl	%ebx, %eax
	movl	%eax, -20(%rbp)
.L5:
	movl	-20(%rbp), %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	fib_local, .-fib_local
	.globl	fib_n
	.type	fib_n, @function
fib_n:
.LFB2:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	pushq	%rbx
	subq	$40, %rsp
	.cfi_offset 3, -24
	movl	%edi, -36(%rbp)
	cmpl	$1, -36(%rbp)
	jg	.L8
	movl	-36(%rbp), %eax
	movl	%eax, -20(%rbp)
	jmp	.L9
.L8:
	movl	-36(%rbp), %eax
	subl	$1, %eax
	movl	%eax, %edi
	call	fib_n
	movl	%eax, %ebx
	movl	-36(%rbp), %eax
	subl	$2, %eax
	movl	%eax, %edi
	call	fib_n
	addl	%ebx, %eax
	movl	%eax, -20(%rbp)
.L9:
	movl	-20(%rbp), %eax
	movq	-8(%rbp), %rbx
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE2:
	.size	fib_n, .-fib_n
	.globl	fib_void
	.type	fib_void, @function
fib_void:
.LFB3:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	movl	$8, -4(%rbp)
	cmpl	$1, -4(%rbp)
	jg	.L12
	movl	-4(%rbp), %eax
	jmp	.L13
.L12:
	movl	-4(%rbp), %eax
	movl	%eax, %edi
	call	fib_n
.L13:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE3:
	.size	fib_void, .-fib_void
	.globl	sum4
	.type	sum4, @function
sum4:
.LFB4:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	%esi, -8(%rbp)
	movl	%edx, -12(%rbp)
	movl	%ecx, -16(%rbp)
	movl	-4(%rbp), %edx
	movl	-8(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%edx, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE4:
	.size	sum4, .-sum4
	.globl	main
	.type	main, @function
main:
.LFB5:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movl	$2, -48(%rbp)
	movl	-48(%rbp), %eax
	sarl	%eax
	movl	%eax, -44(%rbp)
	movl	$29, -40(%rbp)
	movl	$0, -36(%rbp)
	movl	$-1, -32(%rbp)
	movl	-36(%rbp), %eax
	notl	%eax
	movl	%eax, -28(%rbp)
	movl	-32(%rbp), %eax
	notl	%eax
	movl	%eax, -24(%rbp)
	movl	-48(%rbp), %eax
	andl	$3, %eax
	movl	%eax, %edx
	movl	-44(%rbp), %eax
	xorl	$2, %eax
	orl	%edx, %eax
	addl	%eax, %eax
	movl	%eax, -20(%rbp)
	cmpl	$2, -48(%rbp)
	jne	.L17
	addl	$1, -36(%rbp)
.L17:
	cmpl	$0, -48(%rbp)
	je	.L18
	addl	$2, -36(%rbp)
.L18:
	cmpl	$1, -48(%rbp)
	jle	.L19
	addl	$4, -36(%rbp)
.L19:
	cmpl	$2, -48(%rbp)
	jg	.L20
	addl	$8, -36(%rbp)
.L20:
	cmpl	$1, -48(%rbp)
	jle	.L21
	addl	$16, -36(%rbp)
.L21:
	cmpl	$2, -48(%rbp)
	jg	.L23
	addl	$32, -36(%rbp)
	jmp	.L23
.L28:
	movl	-48(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	jne	.L24
	sall	-48(%rbp)
	jmp	.L23
.L24:
	cmpl	$4, -48(%rbp)
	je	.L26
	addl	$2, -48(%rbp)
	sall	$2, -48(%rbp)
	jmp	.L23
.L26:
	cmpl	$4, -48(%rbp)
	jle	.L27
	addl	$1, -44(%rbp)
	jmp	.L23
.L27:
	movl	-48(%rbp), %eax
	orl	%eax, -40(%rbp)
.L23:
	cmpl	$10, -48(%rbp)
	jle	.L28
	movl	$8, %edi
	call	fib_local
	movl	%eax, -16(%rbp)
	call	fib_void
	movl	%eax, -12(%rbp)
	movl	-24(%rbp), %ecx
	movl	-28(%rbp), %edx
	movl	-32(%rbp), %esi
	movl	-36(%rbp), %eax
	movl	%eax, %edi
	call	sum4
	movl	%eax, -8(%rbp)
	movl	-40(%rbp), %eax
	xorl	-44(%rbp), %eax
	andl	$7, %eax
	movl	%eax, -4(%rbp)
	cmpl	$0, -4(%rbp)
	jne	.L29
	addl	$1, -36(%rbp)
	jmp	.L30
.L29:
	cmpl	$1, -4(%rbp)
	jne	.L31
	addl	$2, -36(%rbp)
	jmp	.L30
.L31:
	cmpl	$2, -4(%rbp)
	jne	.L32
	addl	$3, -36(%rbp)
	jmp	.L30
.L32:
	cmpl	$3, -4(%rbp)
	jne	.L33
	addl	$4, -36(%rbp)
	jmp	.L30
.L33:
	cmpl	$4, -4(%rbp)
	jne	.L34
	addl	$5, -36(%rbp)
	jmp	.L30
.L34:
	addl	$6, -36(%rbp)
.L30:
	movl	-48(%rbp), %edx
	movl	-28(%rbp), %ecx
	movl	-36(%rbp), %eax
	movl	%ecx, %esi
	movl	%eax, %edi
	call	test
	movl	-48(%rbp), %edx
	movl	-44(%rbp), %eax
	addl	%eax, %edx
	movl	-40(%rbp), %eax
	addl	%eax, %edx
	movl	-36(%rbp), %eax
	addl	%eax, %edx
	movl	-32(%rbp), %eax
	addl	%eax, %edx
	movl	-28(%rbp), %eax
	addl	%eax, %edx
	movl	-24(%rbp), %eax
	addl	%eax, %edx
	movl	-20(%rbp), %eax
	addl	%eax, %edx
	movl	-16(%rbp), %eax
	addl	%eax, %edx
	movl	-12(%rbp), %eax
	addl	%eax, %edx
	movl	-8(%rbp), %eax
	addl	%edx, %eax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE5:
	.size	main, .-main
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
