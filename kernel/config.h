#define CURRENT_YEAR        2019                            // Change this each year!
// #define CPU_X86_64
#define CPU_X86

//#define	TIMER_1024HZ	1
#define	TIMER_8KHZ	1

#if	defined(CPU_X86) && defined(CPU_X86_64)
#error "Chose either x86 or x86_64 CPU in config.h"
#endif

#if	defined(TIMER_1024HZ) && defined(TIMER_8KHZ)
#error "You must chose only one timer speed (1Khz or 8Khz) in config.h"
#endif
