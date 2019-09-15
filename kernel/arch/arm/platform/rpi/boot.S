.section	.text.boot
.global		_start

_start:
	mrs	x1, mpidr_el1		// read CPU ID
	and	x1, x1, #3
	cbz	x1, 2f			// halt cpus > 0
1:	wfe
	b	1b
2:	// setup stack
	ldr	x1, =_start
	mov	sp, x1

	// clear bss
	ldr	x1, __bss_start
	ldr	w2, __bss_size
3:	cbz	w2, 4f
	str	xzr, [x1], #8
	sub	w2, w2, #1
	cbnz	w2, 3b
4:	bl	main			// jmp to C code
	b	1b			// halt core