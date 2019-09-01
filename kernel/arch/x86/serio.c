#include <sys/stddef.h>
#include <sys/types.h>
#include <core/cons.h>
#include <machine/asm.h>
#include <machine/serio.h>


void md_serio_init(uint32_t port, uint32_t rate) {
     md_outb(port + 1, 0x00);			// disable interrupts
     md_outb(port + 3, 0x80);			// Enable DLAB to set divisor
     md_outb(port + 0, 0x03);			// Set divisor (low byte) to 3 (38400)
     md_outb(port + 1, 0x00);			//  --- high byte
     md_outb(port + 3, 0x03);			// 8N1
     md_outb(port + 2, 0xc7);			// Enable FIFO, clear FIFO, 14 byte threshold
     md_outb(port + 4, 0x0b);
}
