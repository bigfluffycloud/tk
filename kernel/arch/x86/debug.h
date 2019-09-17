#if	!defined(__machine_debug_h)
#define	__machine_debug_h
#include <machine/asm.h>

//outputs a character to the debug console
#define BochsConsolePrintChar(c) md_outb(0xe9, c)

//stops simulation and breaks into the debug console
#define BochsBreak() md_outw(0x8A00,0x8A00); md_outw(0x8A00,0x08AE0);

// "Magic" breakpoint
#define	BochsMagicBreakpoint() __asm__("xchgw %bx, %bx");

#endif	// !defined(__machine_debug_h)
 