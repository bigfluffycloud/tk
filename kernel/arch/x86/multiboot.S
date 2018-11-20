	.globl	_entry
	.extern	cons_write
	.extern md_halt

.set	ALIGN,		(1<<0)		// align modules on page boundaries
.set	MEMINFO,	(1<<1)		// provide memory map
.set	FLAGS,		ALIGN|MEMINFO	// multiboot flags
.set	MAGIC,		0x1badb002	// multiboot magic
.set	CHECKSUM,	-(MAGIC + FLAGS)
.set	STACKSIZE, 0x4000		// 16kb stack

// Multiboot header
.align	4
.long	MAGIC
.long	FLAGS
.long	CHECKSUM

_entry:
	cli
	mov	$(stack + STACKSIZE), %esp
	pushl	$0
	popf
	pushl	%eax			// multiboot magic number
	pushl	%ebx			// multiboot data structure

	call	entry_multiboot		// entry point for multiboot

	pushl	$__exit_str
	call	cons_write

	// bochs breakpoint
	movw	$0x8a00, %ax
	movw	%ax, %dx
	outw	%ax, %dx	// write 0x8a00 -> 0x8a00
	movw	$0x8ae0, %ax
	outw	%ax, %dx	// write 0x8ae0 -> 0x8a00

	// Enter low-power state and hang
	call	md_halt

.comm	stack, STACKSIZE, 32		// reserve stack on quadword boundary

__exit_str:
	.asciz	"Goodbye!\n"
