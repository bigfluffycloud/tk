#if	!defined(__stdio_h)
#define	__stdio_h
#define EOF (-1)
#include <sys/cdefs.h>
#include <core/cons.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int printf(const char* __restrict, ...);
extern int putchar(int);
extern int puts(const char*);

#ifdef	__cplusplus
};
#endif	// __cplusplus
#endif	// !defined(__stdio_h)
