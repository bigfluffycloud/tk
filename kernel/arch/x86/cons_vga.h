#if	!defined(__machine_cons_vga_h)
#define	__machine_cons_vga_h

#include <sys/types.h>
#include <machine/vga.h>
struct	cons {
  uint16_t	curs_x,			// cursor x
                curs_y;			// cursor y
  uint8_t	attr;			// text attributes
  uint16_t	width,
                height;
  uint16_t	*buf;			// buffer ptr (0xb800 for cons0)
};
        
// console text colours
#define	MD_CONS_BLACK	0
#define	MD_CONS_BLUE	1
#define	MD_CONS_GREEN	2
#define	MD_CONS_CYAN	3
#define	MD_CONS_RED	4
#define	MD_CONS_MAGENTA	5
#define	MD_CONS_BROWN	6
#define	MD_CONS_LTGREY	7
#define	MD_CONS_GREY	8
#define	MD_CONS_LTBLUE	9
#define	MD_CONS_LTGREEN	10
#define	MD_CONS_LTCYAN	11
#define	MD_CONS_LTRED	12
#define	MD_CONS_LTMAGENTA 13
#define	MD_CONS_YELLOW	14
#define	MD_CONS_WHITE	15
#define	MD_COLOUR_PAIR(fg, bg)	((bg << 4) | (fg & 0x0f))
// from osdev wiki
//#define	MD_COLOUR_PAIR(bg, fg) (fg | bg << 4)

// World-visible structure exposing virtual consoles
extern struct cons cons;

// Set colour pair
static inline void cons_colour(uint8_t fg, uint8_t bg) {
  cons.attr = MD_COLOUR_PAIR(fg, bg);
}

// Driver Interface
extern void cons_init(void);

// 'Drawing' stuff
extern void cons_clear(void);
extern void cons_put(const char c);
extern void cons_write(const char *str);

// Cursor Management
extern void cons_curs_set(const int x, const int y);
extern void con_curs_enable(uint8_t cursor_start, uint8_t cursor_end);
extern void cons_disable_cursor(void);

#endif	// !defined(__machine_cons_vga_h)
