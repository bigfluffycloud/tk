#if	!defined(__string_h)
#define	__string_h
#include <type.h>

static inline size_t strlen(const char *s) {
  size_t n;

  for (n = 0; s[n]; n++)
     ;

  return n;
}

extern char *strncpy(char *dest, const char *src, size_t n);
extern void *memset(void *dest, const uint8_t val, size_t n);
extern void *memmove(void *dest, void *src, size_t n);

#endif	// !defined(__string_h)
