#if	!defined(__string_h)
#define	__string_h
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

__inline__ size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len])
		len++;
	return len;
}

extern char *strncpy(char *dest, const char *src, size_t n);
extern void *memset(void *dest, const uint8_t val, size_t n);
extern void *memmove(void *dest, const void *src, size_t n);
extern int memcmp(const void*, const void*, size_t);
extern void *memcpy(void* __restrict, const void* __restrict, size_t);

#ifdef	__cplusplus
};
#endif	// __cplusplus

#endif	// !defined(__string_h)
