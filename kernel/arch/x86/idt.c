#include <sys/types.h>
#include <string.h>
#include <cons.h>
#include <machine/idt.h>
#include <machine/isr.h>
#include <machine/except.h>

extern void md_isr(void);	// locore.S

static md_idt_entry md_idt_entries[256];
static md_idt_ptr md_idtptr;

int md_idt_set(uint32_t irq,  uint32_t hndlr, uint16_t flags, uint16_t sel) {
   // XXX: no support for IRQs > 255 on x86{,_64} - we should return a proper error code here
   if (irq > 255)
      return -1;

   md_idt_entries[irq].base_low = hndlr & 0xffff;
   md_idt_entries[irq].base_hi = (hndlr >> 16) & 0xffff;
   md_idt_entries[irq].rsvd = 0;
   md_idt_entries[irq].flags = flags;
   md_idt_entries[irq].sel = sel;
   return 0;
}

void md_idt_init(void) {
  uint16_t flags = 0x8e;	// XXX: Change me

  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("*");
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" setup IDT");

  md_idtptr.limit = sizeof(md_idt_entry) * 256 - 1;
  md_idtptr.base = (uint32_t)&md_idt_entries;

  memset(&md_idt_entries, 0, sizeof(md_idt_entry) * 256);
  cons_colour(CONS_YELLOW, CONS_BLACK);

  // populate IDT with pointers to assembly hooks
  md_idt_set(0, (uint32_t)md_isr_0, 0x08, 0x8e);
  md_idt_set(1, (uint32_t)md_isr_1, 0x08, 0x8e);
  md_idt_set(2, (uint32_t)md_isr_2, 0x08, 0x8e);
  md_idt_set(3, (uint32_t)md_isr_3, 0x08, 0x8e);
  md_idt_set(4, (uint32_t)md_isr_4, 0x08, 0x8e);
  md_idt_set(5, (uint32_t)md_isr_5, 0x08, 0x8e);
  md_idt_set(6, (uint32_t)md_isr_6, 0x08, 0x8e);
  md_idt_set(7, (uint32_t)md_isr_7, 0x08, 0x8e);
  md_idt_set(8, (uint32_t)md_isr_8, 0x08, 0x8e);
  md_idt_set(9, (uint32_t)md_isr_9, 0x08, 0x8e);
  md_idt_set(10, (uint32_t)md_isr_10, 0x08, 0x8e);
  md_idt_set(11, (uint32_t)md_isr_11, 0x08, 0x8e);
  md_idt_set(12, (uint32_t)md_isr_12, 0x08, 0x8e);
  md_idt_set(13, (uint32_t)md_isr_13, 0x08, 0x8e);
  md_idt_set(14, (uint32_t)md_isr_14, 0x08, 0x8e);
  md_idt_set(15, (uint32_t)md_isr_15, 0x08, 0x8e);
  md_idt_set(16, (uint32_t)md_isr_16, 0x08, 0x8e);
  md_idt_set(17, (uint32_t)md_isr_17, 0x08, 0x8e);
  md_idt_set(18, (uint32_t)md_isr_18, 0x08, 0x8e);
  md_idt_set(19, (uint32_t)md_isr_19, 0x08, 0x8e);
  md_idt_set(20, (uint32_t)md_isr_20, 0x08, 0x8e);
  md_idt_set(21, (uint32_t)md_isr_21, 0x08, 0x8e);
  md_idt_set(22, (uint32_t)md_isr_22, 0x08, 0x8e);
  md_idt_set(23, (uint32_t)md_isr_23, 0x08, 0x8e);
  md_idt_set(24, (uint32_t)md_isr_24, 0x08, 0x8e);
  md_idt_set(25, (uint32_t)md_isr_25, 0x08, 0x8e);
  md_idt_set(26, (uint32_t)md_isr_26, 0x08, 0x8e);
  md_idt_set(27, (uint32_t)md_isr_27, 0x08, 0x8e);
  md_idt_set(28, (uint32_t)md_isr_28, 0x08, 0x8e);
  md_idt_set(29, (uint32_t)md_isr_29, 0x08, 0x8e);
  md_idt_set(30, (uint32_t)md_isr_30, 0x08, 0x8e);
  md_idt_set(31, (uint32_t)md_isr_31, 0x08, 0x8e);
  md_idt_set(32, (uint32_t)md_isr_32, 0x08, 0x8e);
  md_idt_set(96, (uint32_t)md_isr_96, 0x08, 0x8e);
  md_idt_set(128, (uint32_t)md_isr_128, 0x08, 0x8e);
  md_idt_flush((uint32_t)&md_idtptr);

  cons_colour(CONS_GREEN, CONS_BLACK);
  cons_write("\t\t\t\tOK\n");
}
