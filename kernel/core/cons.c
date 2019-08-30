#include <core/cons.h>

// cons_vprintf: varargs-enhanced printf for the console.
// the first two args are x/y position (or -1, -1) to print at.
// cons_printf() will always pass -1, -1 as it doesn't care where
// it prints...
void cons_vprintf(int x, int y, const char *fmt, va_list *va) {
}

void cons_printf(const char *fmt, ...) {
     va_list va;
     va_start(va, fmt);

     cons_vprintf(-1, -1, fmt, &va);
     va_end(va);
}

void cons_printf_at(int x, int y, const char *fmt, ...) {
     va_list va;
     va_start(va, fmt);

     cons_vprintf(x, y, fmt, &va);
     va_end(va);
}
