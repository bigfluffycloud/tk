.code32
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
.section .multiboot
.long	MAGIC
.long	FLAGS
.long	CHECKSUM

// Allocate 16kb stack (downward growing)
.section .stack
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:
 
_entry:
	cli
	mov	$stack_top, %esp
	push	$0
	popf
	push	%eax			// multiboot magic number
	push	%ebx			// multiboot data structure

	call	entry_multiboot		// entry point for multiboot

// C code has returned, say goodbye...
	push	$__exit_str
	call	cons_write

	// bochs breakpoint
	movw	$0x8a00, %ax
	movw	%ax, %dx
	outw	%ax, %dx	// write 0x8a00 -> 0x8a00
	movw	$0x8ae0, %ax
	outw	%ax, %dx	// write 0x8ae0 -> 0x8a00

	// Enter low-power state and hang the machine
	call	md_halt

__exit_str:
	.asciz	"Goodbye!\n"

#.size _start, . -  _start
