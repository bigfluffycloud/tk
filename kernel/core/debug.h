#if	!defined(__core_debug_h)
#define	__core_debug_h
#include <machine/debug.h>

extern void debug_serio_init(void);
extern uint32_t debug_serio_read(char *msg);
extern uint32_t debug_serio_write(const char *msg);

#endif	// !defined(__core_debug_h)
