#include <sys/stddef.h>
#include <core/debug.h>

// Set up serial port
void md_debug_serio_init(uint32_t addr, uint32_t speed) {
}

// Returns: uint32_t - Bytes read
uint32_t md_debug_serio_read(char *buf) {
   uint32_t bytes_read = 0;

   return bytes_read;
}

uint32_t md_debug_serio_write(const char *msg) {
   uint32_t bytes_wrote = 0;
   
   return bytes_wrote;
}
