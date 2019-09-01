// stupid simple console driver ;)
// TODO: Make this do double buffering, so scrolling can be nice and smooth?

#include <sys/types.h>
#include <sys/stdint.h>
#include <machine/asm.h>
#include <core/cons.h>
#include <core/ssp.h>
struct cons cons;
 
uint16_t cons_detect_bios_area_hardware(void) {
    const uint16_t* bda_detected_hardware_ptr = (const uint16_t*) 0x410;
    return *bda_detected_hardware_ptr;
}
 
enum video_type cons_get_bios_area_video_type(void) {
    return (enum video_type) (cons_detect_bios_area_hardware() & 0x30);
}

void cons_curs_enable(uint8_t cursor_start, uint8_t cursor_end) {
    md_outb(0x3D4, 0x0A);
    md_outb(0x3D5, (md_inb(0x3D5) & 0xC0) | cursor_start);
    md_outb(0x3D4, 0x0B);
    md_outb(0x3D5, (md_inb(0x3D5) & 0xE0) | cursor_end);
}

void cons_curs_disable(void) {
    md_outb(0x3D4, 0x0A);
    md_outb(0x3D5, 0x20);
}

// Get cursor position
uint16_t cons_curs_get(void) {
    uint16_t pos = 0;
    outb(0x3D4, 0x0F);
    pos |= inb(0x3D5);
    outb(0x3D4, 0x0E);
    pos |= ((uint16_t)inb(0x3D5)) << 8;
    return pos;
}

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

//this is the bitmap font you've loaded
unsigned char *font;

#if	0 
void md_cons_fb_drawchar(unsigned char c, int x, int y, int fgcolor, int bgcolor) {
	int cx,cy;
	int mask[8] = {1, 2, 4, 8, 16, 32, 64, 128};
	unsigned char *gylph = font + (int)c * 16;
 
	for (cy = 0 ; cy < 16; cy++){
	    for (cx = 0; cx < 8; cx++) {
		putpixel(glyph[cy]&mask[cx] ? fgcolor : bgcolor, x + cx, y + cy - 12);
	    }
	}
}

//this is the bitmap font you've loaded
unsigned char *font;
 
void cons_fb_drawchar_transparent(unsigned char c, int x, int y, int fgcolor) {
	int cx, cy;
	int mask[8] = { 1, 2, 4, 8, 16, 32, 64, 128};
	unsigned char *gylph = font + (int)c * 16;
 
	for (cy = 0; cy < 16; cy++) {
            for (cx = 0; cx < 8; cx++) {
		if (glyph[cy]&mask[cx])
                   putpixel(fgcolor,x+cx,y+cy-12);
            }
	}
}

//this is the bitmap font you've loaded
unsigned char *font;
 
void drawchar_8BPP(unsigned char c, int x, int y, int fgcolor, int bgcolor) {
	void *dest;
	uint32_t *dest32;
	unsigned char *src;
	int row;
	uint32_t fgcolor32;
	uint32_t bgcolor32;
 
	fgcolor32 = fgcolor | (fgcolor << 8) | (fgcolor << 16) | (fgcolor << 24);
	bgcolor32 = bgcolor | (bgcolor << 8) | (bgcolor << 16) | (bgcolor << 24);
	src = font + c * 16;
	dest = videoBuffer + y * bytes_per_line + x;
	for (row = 0; row < 16; row++) {
	    if (*src != 0) {
	       mask_low = mask_table[*src][0];
	       mask_high = mask_table[*src][1];
               dest32 = dest;
	       dest32[0] = (bgcolor32 & ~mask_low) | (fgcolor32 & mask_low);
	       dest32[1] = (bgcolor32 & ~mask_high) | (fgcolor32 & mask_high);
            }
	    src++;
	    dest += bytes_per_line;
	}
}
 
void drawchar_transparent_8BPP(unsigned char c, int x, int y, int fgcolor) {
	void *dest;
	uint32_t *dest32;
	unsigned char *src;
	int row;
	uint32_t fgcolor32;
 
	fgcolor32 = fgcolor | (fgcolor << 8) | (fgcolor << 16) | (fgcolor << 24);
	src = font + c * 16;
	dest = videoBuffer + y * bytes_per_line + x;

	for (row = 0; row < 16; row++) {
	    if (*src != 0) {
	        mask_low = mask_table[*src][0];
		mask_high = mask_table[*src][1];
		dest32 = dest;
		dest32[0] = (dest[0] & ~mask_low) | (fgcolor32 & mask_low);
		dest32[1] = (dest[1] & ~mask_high) | (fgcolor32 & mask_high);
            }
	    src++;
	    dest += bytes_per_line;
	}
}
#endif
