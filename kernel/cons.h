#include <machine/cons.h>

#define	CONS_BLACK	MD_CONS_BLACK
#define	CONS_BLUE	MD_CONS_BLUE
#define	CONS_GREEN	MD_CONS_GREEN
#define	CONS_CYAN	MD_CONS_CYAN
#define	CONS_RED	MD_CONS_RED
#define	CONS_MAGENTA	MD_CONS_MAGENTA
#define	CONS_BROWN	MD_CONS_BROWN
#define	CONS_LTGREY	MD_CONS_LTGREY
#define	CONS_GREY	MD_CONS_GREY
#define	CONS_LTBLUE	MD_CONS_LTBLUE
#define	CONS_LTGREEN	MD_CONS_LTGREEN
#define	CONS_LTCYAN	MD_CONS_LTCYAN
#define	CONS_LTRED	MD_CONS_LTRED
#define	CONS_LTMAGENTA	MD_CONS_LTMAGENTA
#define	CONS_YELLOW	MD_CONS_YELLOW
#define	CONS_WHITE	MD_CONS_WHITE

// This abstracts for funny consoles...
#define	COLOUR_PAIR(fg, bg) MD_COLOUR_PAIR(fg, bg)
