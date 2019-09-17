#include <config.h>
#if	defined(CPU_X86)
.code32
#endif
#if	defined(CPU_X86_64)
.code64
#endif
	.global md_gdt_flush
md_gdt_flush:
	mov	4(%esp), %eax	// get ptr to gdt
	lgdt	(%eax)

	mov	$0x10, %ax	// offset in gdt to data segment
	mov	%ax, %ds
//
	mov	%ax, %es
	mov	%ax, %fs
	mov	%ax, %gs
	mov	%ax, %ss

	jmp	$0x08, $_flush
_flush:
	ret

	.global	md_idt_flush
md_idt_flush:
	mov	4(%esp), %eax
	lidt	(%eax)
	ret
