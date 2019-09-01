#include <sys/types.h>
#include <sys/stddef.h>
#include <machine/asm.h>
#include <machine/pic.h>
#include <cons.h>

// Initially we mask off all IRQs *except* cascade (irq 2)
static uint16_t irqmask = 0xFFFF & ~(1 << CASCADE);

void md_pic_mask_set(uint8_t mask) {
  irqmask = mask;

  md_outb(IO_PIC1+1, mask);
  md_outb(IO_PIC2+1, mask >> 8);
}

void md_pic_init(void) {
  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("*");
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" remap interrupts (8259)");

  // Configure the 8259 operation mode
  md_outb(IO_PIC1+1, 0xff);		// mask all ints on master
  md_outb(IO_PIC2+1, 0xff);		// mask all ints on slave

  // ICW1: 0001g0hi
  // 	g: 0=edge, 1=level triggered
  //	h: 0=cascade, 1=single (master only)
  //	i: 0=not sending ICW4, 1=will send ICW4
  md_outb(IO_PIC1, 0x11);		// send ICW1 to master PIC
  md_outb(IO_PIC2, 0x11);		// send ICW1 to slave PIC

  // ICW2: Vector offset: IRQ 1 = INT 32 (0x20)
  md_outb(IO_PIC1 + 1, IRQ_OFFSET);	// send ICW2 to master PIC
  md_outb(IO_PIC2 + 1, IRQ_OFFSET+8);	// send ICW2 to slave PIC

  // Master PIC: ICW3: bitmask of IRQ lines which slaves
  md_outb(IO_PIC1 + 1, 1<<CASCADE);	// send ICW3 to master PIC
  // Slave PIC: ICW3: 3 bit IRQ of slave connection to master
  md_outb(IO_PIC2 + 1, CASCADE);	// send ICW3 to slave PICaa

  // ICW4: 000nbmap
  //	n: 1=special fully nested map (uh ok?)
  //	b: 1=buffered mode
  //	m: 0=Slave PIC, 1=master PIC [ignored if b=0]
  //	a: 1=Automatic EOI (broken on slave)
  //	p: 0=MCS-80/85 (historic), 1=x86 mode
  md_outb(IO_PIC1 + 1, 0x05);		// send ICW4 to master PIC
  md_outb(IO_PIC2 + 1, 0x01);		// send ICW4 to slave PIC

  // OCW3: 0ee01prr
  //   ee: 10=Clear Specific mask, 11=Set specific mask
  //	p: 0=Non-polling, 1=Polling
  //   rr: 10=Read IRR, 11=Read ISR
  md_outb(IO_PIC1, 0x68);		// Clear specific mask
  md_outb(IO_PIC2, 0x68);
  md_outb(IO_PIC1, 0x0a);		// Read IR
  md_outb(IO_PIC2, 0x0a);

  cons_colour(CONS_GREEN, CONS_BLACK);
  cons_write("\t\tOK\n");

  if (irqmask != 0xffff)
     md_pic_mask_set(irqmask);
}

void	md_pic_eoi(const uint8_t irq) {
  if (irq >= 8)
     md_outb(IO_PIC2, 0x20);

  md_outb(IO_PIC1, 0x20);
}

void md_nmi_enable(void) {
     md_outb(0x70, md_inb(0x70) & 0x7f);
}

void md_nmi_disable(void) {
     md_outb(0x70, md_inb(0x70) | 0x80);
}
