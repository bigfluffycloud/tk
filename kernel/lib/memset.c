#include <type.h>
#include <string.h>

void *memset(void *dest, const uint8_t val, size_t n) {
    register unsigned char *ptr = (unsigned char *)dest;

    while (n-- > 0)
       *ptr++ = val;

    return dest;
}
