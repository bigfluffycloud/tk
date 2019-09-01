//
// Here we implement common console code, shared between all console types...
//
#include <core/cons.h>
#define SSFN_NOIMPLEMENTATION               /* don't include the normal renderer implementation */
#define SSFN_CONSOLEBITMAP_HICOLOR          /* use the special renderer for hicolor packed pixels */
#include <ssfn.h>

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

#if	0
void cons_fb_renderer_put(void) {
     /* set up context by global variables */
     ssfn_font = &_binary_console_sfn_start;     /* the bitmap font to use */
     ssfn_dst_ptr = 0xE0000000;                  /* framebuffer address and bytes per line */
     ssfn_dst_pitch = 4096;
     ssfn_fg = 0xFFFF;                           /* colors, white on black */
     ssfn_bg = 0;
     ssfn_x = 100;                               /* coordinates to draw to */
     ssfn_y = 200;

     /* render one glyph directly to the screen and then adjust ssfn_x and ssfn_y */
     ssfn_putc(0x41);
}

/* the linear framebuffer */
extern char *fb;
/* number of bytes in each line, it's possible it's not screen width * bytesperpixel! */
extern int scanline;
/* import our font that's in the object file we've created above */
extern char _binary_font_start;
 
void fb_putchar(
    /* note that this is int, not char as it's a unicode character */
    unsigned short int c,
    /* cursor position on screen, in characters not in pixels */
    int cx, int cy,
    /* foreground and background colors, say 0xFFFFFF and 0x000000 */
    uint32_t fg, uint32_t bg) {
    /* cast the address to PSF header struct */
    PSF_font *font = (PSF_font*)&_binary_font_psf_start;
    /* we need to know how many bytes encode one row */
    int bytesperline=(font->width+7)/8;
    /* unicode translation */
    if (unicode != NULL) {
       c = unicode[c];
    }
    /* get the glyph for the character. If there's no
       glyph for a given character, we'll display the first glyph. */
    unsigned char *glyph =
     (unsigned char*)&_binary_font_psf_start +
     font->headersize +
     (c > 0 && c < font->numglyph ? c : 0) * font->bytesperglyph;
    /* calculate the upper left corner on screen where we want to display.
       we only do this once, and adjust the offset later. This is faster. */
    int offs =
        (cy * font->height * scanline) +
        (cx * (font->width + 1) * 4);
    /* finally display pixels according to the bitmap */
    int x,y, line,mask;

    for (y = 0; y < font->height; y++){
        /* save the starting position of the line */
        line=offs;
        mask = 1 << (font->width - 1);
        /* display a row */
        for (x=0;x<font->width;x++){
            *((uint32_t*)(&fb + line)) = ((int)*glyph) & (mask) ? fg : bg;
            /* adjust to the next pixel */
            mask >>= 1;
            line += 4;
        }
        /* adjust to the next line */
        glyph += bytesperline;
        offs  += scanline;
    }
}
#endif
