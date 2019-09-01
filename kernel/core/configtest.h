
#if	defined(CPU_X86) && defined(CPU_X86_64)
#error "Chose either x86 or x86_64 CPU in config.h"
#endif

#if	defined(TIMER_1024HZ) && defined(TIMER_8KHZ)
#error "You must chose only one timer speed (1Khz or 8Khz) in config.h"
#endif
