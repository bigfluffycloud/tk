#include <sys/types.h>
#include <string.h>

void *memset(void* bufptr, const uint8_t value, size_t size) {
     register unsigned char* buf = (unsigned char*) bufptr;

     for (size_t i = 0; i < size; i++)
        buf[i] = (unsigned char) value;
     return bufptr;
}
