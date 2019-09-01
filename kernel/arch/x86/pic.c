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

void md_pic_fini(void) {
  __asm__ __volatile__ ("mov $0xff, %al; out %al, $0xa1; out %al, $0x21");
}

void md_pic_init(void) {
  unsigned char a1, a2;

  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("*");
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" remap interrupts (8259)");

  // Save state
  a1 = md_inb(IO_PIC1+1);
  a2 = md_inb(IO_PIC2+1);

  // Configure the 8259 operation mode
  md_outb(IO_PIC1+1, 0xff);		// mask all ints on master
  md_io_wait();
  md_outb(IO_PIC2+1, 0xff);		// mask all ints on slave
  md_io_wait();

  // ICW1: 0001g0hi
  // 	g: 0=edge, 1=level triggered
  //	h: 0=cascade, 1=single (master only)
  //	i: 0=not sending ICW4, 1=will send ICW4
  md_outb(IO_PIC1, 0x11);		// send ICW1 to master PIC
  md_io_wait();
  md_outb(IO_PIC2, 0x11);		// send ICW1 to slave PIC

  // ICW2: Vector offset: IRQ 1 = INT 32 (0x20)
  md_outb(IO_PIC1 + 1, IRQ_OFFSET);	// send ICW2 to master PIC
  md_io_wait();
  md_outb(IO_PIC2 + 1, IRQ_OFFSET+8);	// send ICW2 to slave PIC

  // Master PIC: ICW3: bitmask of IRQ lines which slaves
  md_outb(IO_PIC1 + 1, 1<<CASCADE);	// send ICW3 to master PIC
  md_io_wait();
  // Slave PIC: ICW3: 3 bit IRQ of slave connection to master
  md_outb(IO_PIC2 + 1, CASCADE);	// send ICW3 to slave PICaa
  md_io_wait();

  // ICW4: 000nbmap
  //	n: 1=special fully nested map (uh ok?)
  //	b: 1=buffered mode
  //	m: 0=Slave PIC, 1=master PIC [ignored if b=0]
  //	a: 1=Automatic EOI (broken on slave)
  //	p: 0=MCS-80/85 (historic), 1=x86 mode
  md_outb(IO_PIC1 + 1, 0x05);		// send ICW4 to master PIC
  md_outb(IO_PIC2 + 1, 0x01);		// send ICW4 to slave PIC
  md_io_wait();

  // OCW3: 0ee01prr
  //   ee: 10=Clear Specific mask, 11=Set specific mask
  //	p: 0=Non-polling, 1=Polling
  //   rr: 10=Read IRR, 11=Read ISR
  md_outb(IO_PIC1, 0x68);		// Clear specific mask
  md_outb(IO_PIC2, 0x68);
  md_io_wait();
  md_outb(IO_PIC1, 0x0a);		// Read IR
  md_outb(IO_PIC2, 0x0a);
  md_io_wait();

  cons_colour(CONS_GREEN, CONS_BLACK);
  cons_write("\t\tOK\n");

  if (irqmask != 0xffff)
     md_pic_mask_set(irqmask);
}

void	md_pic_eoi(const uint8_t irq) {
  if (irq >= 8)
     md_outb(IO_PIC2, PIC_CMD_EOI);

  md_outb(IO_PIC1, PIC_CMD_EOI);
}

/* Helper func */
static uint16_t md_pic_get_irq_reg(int ocw3) {
    /* OCW3 to PIC CMD to get the register values.  PIC2 is chained, and
     * represents IRQs 8-15.  PIC1 is IRQs 0-7, with 2 being the chain */
    md_outb(IO_PIC1, ocw3);
    md_outb(IO_PIC2, ocw3);
    return (md_inb(IO_PIC2) << 8) | md_inb(IO_PIC1);
}
 
/* Returns the combined value of the cascaded PICs irq request register */
uint16_t md_pic_get_irr(void) {
    return md_pic_get_irq_reg(PIC_READ_IRR);
}
 
/* Returns the combined value of the cascaded PICs in-service register */
uint16_t md_pic_get_isr(void) {
    return md_pic_get_irq_reg(PIC_READ_ISR);
}

void md_nmi_enable(void) {
     md_outb(0x70, md_inb(0x70) & 0x7f);
}

void md_nmi_disable(void) {
     md_outb(0x70, md_inb(0x70) | 0x80);
}
