#if	!defined(__machine_serio_h)
#define	__machine_serio_h

#define	IRQ_COM1		4
#define	IRQ_COM2		3
#define	IRQ_COM3		4
#define	IRQ_COM4		3

#define	IO_COM1			0x3f8
#define	IO_COM2			0x2f8
#define	IO_COM3			0x3e8
#define	IO_COM4			0x2e8

// Interrupt Enable Register
#define	UART_INT_DATA_READY	0x01
#define	UART_INT_TRANSMIT_EMPTY	0x02
#define	UART_INT_BREAK_ERROR	0x04
#define	UART_INT_STATUS		0x08

// Status
#define	UART_STATUS_DATA_READY		0x01
#define	UART_STATUS_OVERRUN		0x02
#define	UART_STATUS_PARITY_ERROR	0x04
#define	UART_STATUS_FRAMING_ERROR	0x08
#define UART_STATUS_BREAK		0x10
#define	UART_EMPTY			0x20
#define	UART_IMPENDING_ERROR		0x40

extern void md_serio_init(uint32_t port, uint32_t rate);

#endif	// !define(__machine_serio_h)
