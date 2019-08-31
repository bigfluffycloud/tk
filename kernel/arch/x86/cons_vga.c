// stupid simple console driver ;)
// TODO: Make this do double buffering, so scrolling can be nice and smooth?

#include <type.h>
#include <machine/asm.h>
#include <core/cons.h>
#include <core/ssp.h>
struct cons cons;

// <ESC>[x;yH or <ESC>[H (0,0) Position the cursor
void	cons_curs_set(const int x, const int y) {
  uint16_t curs_pos = (y * cons.width) + x;

  cons.curs_x = x;
  cons.curs_y = y;
  md_outb(0x3d4, 0x0f);			// set low cursor byte
  md_outb(0x3d5, curs_pos);
  md_outb(0x3d4, 0x0e);			// set high cursor byte
  md_outb(0x3d5, curs_pos >> 8);
}

// <ESC>DScroll down one line
static	void	cons_scroll(void) {
  // set blank to SPC and appropriate colour
  uint16_t	blank = 0x20 | (cons.attr << 8);

  if (cons.curs_y >= cons.height) {
      int i;

      for (i = 0; i < (cons.height - 1) * cons.width; i++)
         cons.buf[i] = cons.buf[i + cons.width];

      for (i = ((cons.height - 1) * cons.width); i < (cons.height * cons.width); i++)
         cons.buf[i] = blank;

      cons.curs_y = cons.height - 1;
  }
}

// Clear the console
void cons_clear(void) {
   // set blank to SPC and appropriate color
   uint16_t blank = 0x20 | (cons.attr << 8);
   int i;

   for (i = 0; i < (cons.width * cons.height); i++)
       cons.buf[i] = blank;

   cons.curs_x = cons.curs_y = 0;
   cons_curs_set(cons.curs_x, cons.curs_y);
}

void cons_put(const char c) {
   uint16_t *loc;

   if (c == 0x08 && cons.curs_x) 		// BKSPC
      cons.curs_x--;
   else if (c == 0x09) {			// TAB
      cons.curs_x = (cons.curs_x + 8) & ~(8-1);
      if (cons.curs_x >= cons.width) {
         cons.curs_x = 0;
         cons.curs_y++;
      }
   } else if (c == '\r')			// CR
      cons.curs_x = 0;
   else if (c == '\n') {			// LF
      cons.curs_x = 0;
      cons.curs_y++;
   } else if (c >= ' ') {			// Other printable char
      loc = cons.buf + (cons.curs_y * cons.width + cons.curs_x);
      *loc = c | (cons.attr << 8);
      cons.curs_x++;
   }

   // Check for End of screen
   if (cons.curs_x >= cons.width) {
      cons.curs_x = 0;
      cons.curs_y++;
   }

   cons_scroll();
   cons_curs_set(cons.curs_x, cons.curs_y);
}

void cons_write(const char *str) {
   int i = 0;

   while (str[i])
      cons_put(str[i++]);
}

void cons_init(void) {
  cons.height = 25;
  cons.width = 80;
  cons.curs_x = cons.curs_y = 0;
  cons.buf = (uint16_t *)0xb8000;
  cons_clear();
}