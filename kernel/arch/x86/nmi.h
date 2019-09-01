#if	!defined(__machine_nmi_h)
#define	__machine_nmi_h

#define	IO_NMI_SCP_A	0x92
#define	IO_NMI_SCP_B	0x61

// these are bits, use with bit_* macros
// Port A (0x92)
#define	NMI_ALT_HOT_RESET	0
#define	NMI_ALT_GATE_A20	1
#define	NMI_RESERVED		2
#define	NMI_SECURITY_LOCK	3
#define	NMI_WATCHDOG		4
#define	NMI_RESERVED2		5
#define	NMI_HDD2_ACT		6
#define	NMI_HDD1_ACT		7

// Port B (0x61)
#define	NMI_TIMER0_SPKR		0
#define	NMI_SPEAKER_DATA_ENABLE	1
#define	NMI_PARITY_ENABLE	2
#define	NMI_CHAN_CHECK_ENABLE	3
#define	NMI_REFRESH_REQUEST	4
#define	NMI_TIMER2_OUTPUT	5
#define	NMI_CHAN_CHECK		6
#define NMI_PARITY		7

#endif	// !defined(__machine_nmi_h)
