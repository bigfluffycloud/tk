#if	!defined(__machine_pic_h)
#define	__machine_pic_h

#define	IO_PIC1	0x20		// master PIC
#define	IO_PIC2	0xa0		// slave PIC
#define	IRQ_OFFSET 0x20		// Offset of IRQ to INT mapping (32)
#define	CASCADE	2		// IRQ for slave

// 8259 PIC Commands
#define	PIC_CMD_EOI		0x20	// End of Interrupt
#define PIC_READ_IRR            0x0a    /* OCW3 irq ready next CMD read */
#define PIC_READ_ISR            0x0b    /* OCW3 irq service next CMD read */

// ICW1
#define	PIC_ICW1_ICW4		0x01	// ICW4 (not) needed
#define	PIC_ICW1_SINGLE		0x02	// cascade mode
#define	PIC_ICW1_INTERVAL4	0x04	// call address interval 4 (8)
#define	PIC_ICW1_LEVEL		0x08	// level (edge) triggered mode
#define	PIC_ICW1_INIT		0x10	// initialization

// ICW4
#define	PIC_ICW4_8086		0x01	// 8086/88 (MCS-80/85) mode
#define	PIC_ICW4_AUTO		0x02	// auto (normal) EOI
#define	PIC_ICW4_BUF_SLAVE	0x08	// buffered mode, slave
#define	PIC_ICW4_BUF_MASTER	0x0c	// buffered mode, master
#define	PIC_ICW4_SFNM		0x10	// special "fully nested" mode

extern void md_pic_mask_set(uint8_t mask);
extern void md_pic_fini(void);
extern void md_pic_init(void);
extern void md_pic_eoi(const uint8_t irq);
extern void md_nmi_enable(void);
extern void md_nmi_disable(void);
extern uint16_t md_pic_get_irr(void);
extern uint16_t md_pic_get_isr(void);

#endif	// !defined(__machine_h)
