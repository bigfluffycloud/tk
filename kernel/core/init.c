#include <type.h>
#include <core/ssp.h>
#include <cons.h>
#include <machine/reboot.h>

void	init(void) {
  cons_colour(CONS_YELLOW, CONS_BLACK);
  cons_write("\n[");
  cons_colour(CONS_CYAN, CONS_BLACK);
  cons_write("global");
  cons_colour(CONS_YELLOW, CONS_BLACK);
  cons_write("]\n");
  __stack_chkguard_setup();

  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write("\n");
  md_halt();
}
