#if	!defined(__machine_rtc_h)
#define	__machine_rtc_h

#include <sys/stddef.h>
#include <sys/types.h>

#define	IO_RTC_REGISTER	0x70
#define	IO_RTC_DATA	0x71

#define	IRQ_RTC		8

extern void md_rtc_write(uint8_t reg, uint8_t val);
extern void md_rtc_timer_init(void);

#endif	// !defined(__machine_rtc_h)
