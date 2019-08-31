#if	!defined(__stdlib_h)
#define	__stdlib_h
#include <sys/cdefs.h>
#ifdef __cplusplus
extern "C" {
#endif

#define MAX(a, b)	(a) > (b) ? (a) : (b)
#define MIN(a, b)	(a) < (b) ? (a) : (b)

extern int atoi(const char *s);
extern unsigned long random(void);
extern void srandom(unsigned long seed);

__attribute__((__noreturn__)) extern void abort(void);

#ifdef	__cplusplus
};
#endif

#endif	// !defined(__stdlib_h)
