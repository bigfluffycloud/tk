#if	!defined(__machine_ps2_h)
#define	__machine_ps2_h

#define	IO_PS2_DATA	0x60
#define	IO_PS2_STATUS	0x64
#define	IO_PS2_COMMAND	0x64

#define	PS2_STATUS_OUTBUF	0
#define	PS2_STATUS_INBUF	1
#define	PS2_STATUS_SYSFLAG	2	
#define PS2_STATUS_COMMAND	3
#define	PS2_STATUS_UNKNOWN	4
#define PS2_STATUS_UNKNOWN2	5
#define	PS2_STATUS_TMEOUT	6
#define PS2_STATUS_PARITY_ERROR 7

#endif	// !defined(__machine_ps_2)
