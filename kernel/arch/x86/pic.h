#if	!defined(__machine_pic_h)
#define	__machine_pic_h

#define	IO_PIC1	0x20		// master PIC
#define	IO_PIC2	0xa0		// slave PIC
#define	IRQ_OFFSET 0x20		// Offset of IRQ to INT mapping (32)
#define	CASCADE	2		// IRQ for slave

extern void md_pic_mask_set(uint8_t mask);
extern void md_pic_init(void);
extern void md_pic_eoi(const uint8_t irq);
extern void md_nmi_enable(void);
extern void md_nmi_disable(void);

#endif	// !defined(__machine_h)
