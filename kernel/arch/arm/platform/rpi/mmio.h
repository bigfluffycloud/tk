#if	!defined(__platform_mmio_h)
#define	__platform_mmio_h

#define	MMIO_TIMER	0x3f003000	// system timer
#define	MMIO_INTR_CONT	0x3f00b000	// interrupt controller
#define	MMIO_VIDEOCORE	0x3f00b880	// videocore mailbox
#define	MMIO_POWERMGMT	0x3f100000	// power management
#define	MMIO_RNG	0x3f104000	// random number generator
#define	MMIO_GPIO_CONT	0x3f200000	// GPIO controller
#define	MMIO_SERIO0	0x3f201000	// UART0
#define	MMIO_SERIO1	0x3f215000	// UART1
#define	MMIO_SDCARD	0x3f300000	// SD card interface
#define	MMIO_USB	0x3f980000	// USB controller

#endif	// !defined(__platform_mmio_h)
