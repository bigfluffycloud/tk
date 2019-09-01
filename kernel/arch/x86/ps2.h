#if	!defined(__machine_ps2_h)
#define	__machine_ps2_h

#define	IO_PS2_DATA	0x60
#define	IO_PS2_STATUS	0x64
#define	IO_PS2_COMMAND	0x64

#define	PS2_STATUS_OUTBUF	0x01
#define	PS2_STATUS_INBUF	0x02
#define	PS2_STATUS_SYSFLAG	0x04	
#define PS2_STATUS_COMMAND	0x08
#define	PS2_STATUS_UNKNOWN	0x10
#define PS2_STATUS_UNKNOWN2	0x20
#define	PS2_STATUS_TMEOUT	0x40
#define PS2_STATUS_PARITY_ERROR 0x80

// Commands
#define	PS2_CMD_SET_LEDS	0xed
#define	PS2_CMD_ECHO		0xee
#define	PS2_CMD_CODESET		0xf0
#define	PS2_CMD_IDENTIFY	0xf2
#define	PS2_CMD_TYPEMATIC	0xf3
#define	PS2_CMD_ENABLE_SCAN	0xf4
#define	PS2_CMD_DISABLE_SCAN	0xf5
#define	PS2_CMD_DEFAULTS	0xf6
#define	PS2_CMD_RESEND		0xfe
#define	PS2_CMD_SELFTEST	0xff

// LED bitmask
#define	PS2_LED_SCROLL		0x01
#define	PS2_LED_NUM		0x02
#define	PS2_LED_CAPS		0x04

// Scan code set
#define PS2_SCANCODE_GET	0
#define	PS2_SCANCODE_SET1	1
#define	PS2_SCANCODE_SET2	2
#define	PS2_SCANCODE_SET3	3

// Special bytes
#define	PS2_BYTE_ERROR		0x00
#define	PS2_BYTE_SELFTEST_OK	0xaa
#define PS2_BYTE_ECHO_REPLY	0xee
#define	PS2_BYTE_ACK		0xfa
#define	PS2_BYTE_SELFTEST_FAIL1 0xfc
#define	PS2_BYTE_SELFTEST_FAIL2	0xfd
#define	PS2_BYTE_RESEND		0xfe	// please repeat last command
#define	PS2_BYTE_ERROR2		0xff

#endif	// !defined(__machine_ps_2)
