md_isr_common:
	pusha			// push edi,esiebp,esp,ebx,edx,ecx,eax

	// save segment selector
	movw	%ds, %ax
	push	%eax

	// load kernel data segment
	mov	$0x10, %ax
	mov	%ax, %ds
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs

	call	md_isr_c	// call C isr handler

	// restore original data segment
	pop	%eax
	mov	%ax, %ds
	mov	%ax, %fs
	mov	%ax, %gs

	popa
	add	$0x0, %esp
	sti
	iret

///////////////
// ISR stuff //
///////////////
// Ugly but could be worse ;)
// If ec = 1, has error code, else doesnt
.macro isr num, ec=0
	.globl md_isr_\num
md_isr_\num:
	cli
.ifne	\ec
	push	$0
.endif
	push	$\num
	call	md_isr_common
.endm

isr 0
isr 1
isr 2
isr 3
isr 4
isr 5
isr 6
isr 7
isr 8, 1
isr 9
isr 10, 1
isr 11, 1
isr 12, 1
isr 13, 1
isr 14, 1
isr 15
isr 16
isr 17
isr 18
isr 19
isr 20
isr 21
isr 22
isr 23
isr 24
isr 25
isr 26
isr 27
isr 28
isr 29
isr 30
isr 31
isr 32
isr 96	// 0x60: native syscalls (legacy mode)
isr 128	// 0x80: compat syscalls
