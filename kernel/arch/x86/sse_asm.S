#include <config.h>
.globl sse_check
.globl sse_enable

sse_check:
	mov $0x1, %eax
	cpuid
	test 1<<25, %edx
	jz .noSSE

//SSE is available
.yesSSE:

//SSE is unavailable
.noSSE:

	ret

sse_enable:
	// now enable SSE and the like
#if	defined(CPU_X86)
	mov %cr0, %eax
	and $0xFFFB, %ax	// clear coprocessor emulation CR0.EM
	or $0x2, %ax		// set coprocessor monitoring  CR0.MP
	mov %eax, %cr0
	mov %cr0, %eax
	or 3 << 9, %ax		// set CR4.OSFXSR and CR4.OSXMMEXCPT at the same time
	mov %eax, %cr0
	ret
#endif	// defined(CPU_X86)

#if	defined(CPU_X86_64)
enable_avx:
	push %rax
	push %rcx
	xor %rcx, %rcx
	xgetbv 			// Load XCR0 register
	or 7, %eax 		// Set AVX, SSE, X87 bits
	xsetbv			// Save back to XCR0
	pop %rcx
	pop %rax
	ret
#endif	// defined(CPU_X86_64)
