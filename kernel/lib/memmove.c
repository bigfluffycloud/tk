#include <type.h>
#include <string.h>

void *memmove(void *dest, void *src, size_t n) {
  char	*t_dst = dest,
        *t_src = src;

  while (n-- > 0)
    *t_dst++ = *t_src++;

  return t_dst;
}
