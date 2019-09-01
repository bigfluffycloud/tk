#include <sys/stddef.h>
#include <sys/types.h>
#include <machine/asm.h>
#include <machine/rtc.h>

void md_rtc_write(uint8_t reg, uint8_t val) {
    if (reg == 0)
       return;
    md_disable_interrupts();
    md_outb(IO_RTC_REGISTER, reg);
    md_outb(IO_RTC_DATA, val);
    md_enable_interrupts();
}

void md_rtc_timer_init(void) {
    char *prev;
//    uint32_t freq = 32768 >> (rate-1);
    uint32_t rate = 0x0f;
    md_disable_interrupts();

#if	defined(TIMER_1024HZ)
    md_outb(IO_RTC_REGISTER, 0x8b);		// select register 8, disable NMI
    prev = md_inb(IO_RTC_DATA);
    md_outb(IO_RTC_REGISTER, 0x8b);
    md_outb(IO_RTC_DATA, prev | 0x40);
#endif

#if	defined(TIMER_8KHZ)
    md_outb(IO_RTC_REGISTER, 0x8a);		// select register A, disable NMI
    prev = md_inb(IO_RTC_DATA);
    md_outb(IO_RTC_REGISTER, 0x8a);
    md_outb(IO_RTC_DATA, (prev & 0xf0) | ate);
#endif
    
    // XXX: register IRQ 8 handler
    md_enable_interrupts();
}
