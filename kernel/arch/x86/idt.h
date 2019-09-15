#if	!defined(__machine_idt_h)
#define	__machine_idt_h
#include <config.h>
#include <sys/types.h>

#if	defined(CPU_X86)
struct md_idt_entry {
  uint16_t	base_low;	// lower 16 bits of ISR
  uint16_t	selector;	// segment selector
  uint8_t	rsvd;		// always 0
  uint8_t	flags;
  uint16_t	base_hi;	// upper 16 bits of ISR
} __attribute__((packed));
#endif

#if	defined(CPU_X86_64)
struct md_idt_entry {
  uint16_t	base_low;
  uint16_t	selector;
  uint8_t	ist;		// bits 0-2 interrupt stack table offset, rest 0
  uint8_t	flags;		// type & attributes;
  uint16_t	base_hi;
  uint32_t	base_top;
  uint32_t	zero;
} __attribute__((packed));
#endif

struct md_idt_ptr {
  uint16_t limit;
  uint32_t base;
};
typedef struct md_idt_entry md_idt_entry;


typedef struct md_idt_ptr md_idt_ptr;
extern void md_idt_flush(uint32_t ptr);     // locore.S
extern int md_idt_set(uint32_t irq, uint32_t hndlr, uint16_t flags, uint16_t sel);
extern void md_idt_init(void);

#endif	// !defined(__machine_idt_h)
