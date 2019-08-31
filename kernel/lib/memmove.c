#include <type.h>
#include <string.h>

void *memmove(void *dest, const void *src, size_t n) {
  char	*t_dst = dest;
  const char *t_src = src;

  while (n-- > 0)
    *t_dst++ = *t_src++;

  return t_dst;
}
