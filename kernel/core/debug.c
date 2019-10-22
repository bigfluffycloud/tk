#include <config.h>
#include <core/debug.h>

void debug_serio_init(void) {
   md_debug_serio_init(CONFIG_SERIO_DEBUG_PORT, CONFIG_SERIO_DEBUG_SPEED);
}

uint32_t debug_serio_read(char *msg) {
   return md_debug_serio_read(msg);
}

uint32_t debug_serio_write(const char *msg) {
   return md_debug_serio_write(msg);
}
