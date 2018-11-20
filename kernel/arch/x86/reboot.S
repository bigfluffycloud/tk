	.globl md_reboot

md_reboot:
	lidt	null_idt
	int	$0

	.globl	md_halt
md_halt:
	cli
__hlt_loop:
	hlt
	jmp	__hlt_loop

null_idt:
	.byte	0
