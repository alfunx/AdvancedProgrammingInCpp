	.file	"main.cpp"
	.text
	.section	.text.startup,"ax",@progbits
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB1541:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movdqa	.LC0(%rip), %xmm0
	movdqa	.LC1(%rip), %xmm2
	xorl	%eax, %eax
	movdqa	.LC2(%rip), %xmm4
	.p2align 4,,10
	.p2align 3
.L2:
	movdqa	%xmm2, %xmm3
	movdqa	%xmm2, %xmm1
	paddd	%xmm4, %xmm2
	addl	$1, %eax
	pmuludq	%xmm0, %xmm3
	psrlq	$32, %xmm1
	psrlq	$32, %xmm0
	pmuludq	%xmm0, %xmm1
	pshufd	$8, %xmm3, %xmm0
	pshufd	$8, %xmm1, %xmm1
	punpckldq	%xmm1, %xmm0
	cmpl	$2499, %eax
	jne	.L2
	movdqa	%xmm0, %xmm2
	movdqa	%xmm0, %xmm1
	leaq	_ZSt4cout(%rip), %rdi
	psrldq	$8, %xmm2
	psrlq	$32, %xmm0
	pmuludq	%xmm2, %xmm1
	psrlq	$32, %xmm2
	pmuludq	%xmm2, %xmm0
	pshufd	$8, %xmm1, %xmm1
	pshufd	$8, %xmm0, %xmm0
	punpckldq	%xmm0, %xmm1
	movdqa	%xmm1, %xmm0
	psrldq	$4, %xmm1
	pmuludq	%xmm1, %xmm0
	movd	%xmm0, %eax
	leal	(%rax,%rax,2), %esi
	sall	$3, %esi
	call	_ZNSolsEi@PLT
	movq	%rax, %rdi
	call	_ZSt4endlIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_@PLT
	xorl	%eax, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE1541:
	.size	main, .-main
	.p2align 4,,15
	.type	_GLOBAL__sub_I_main, @function
_GLOBAL__sub_I_main:
.LFB2027:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	leaq	_ZStL8__ioinit(%rip), %rdi
	call	_ZNSt8ios_base4InitC1Ev@PLT
	movq	_ZNSt8ios_base4InitD1Ev@GOTPCREL(%rip), %rdi
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	leaq	__dso_handle(%rip), %rdx
	leaq	_ZStL8__ioinit(%rip), %rsi
	jmp	__cxa_atexit@PLT
	.cfi_endproc
.LFE2027:
	.size	_GLOBAL__sub_I_main, .-_GLOBAL__sub_I_main
	.section	.init_array,"aw"
	.align 8
	.quad	_GLOBAL__sub_I_main
	.local	_ZStL8__ioinit
	.comm	_ZStL8__ioinit,1,1
	.section	.rodata.cst16,"aM",@progbits,16
	.align 16
.LC0:
	.long	1
	.long	1
	.long	1
	.long	1
	.align 16
.LC1:
	.long	10000
	.long	9999
	.long	9998
	.long	9997
	.align 16
.LC2:
	.long	-4
	.long	-4
	.long	-4
	.long	-4
	.hidden	__dso_handle
	.ident	"GCC: (GNU) 8.2.1 20180831"
	.section	.note.GNU-stack,"",@progbits
