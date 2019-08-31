#include <type.h>
#include <cons.h>
#include <machine/vmm.h>

void md_vmm_init(void) {
  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("*");
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" setup VMM");

  // Do stuff
  cons_colour(CONS_GREEN, CONS_BLACK);
  cons_write("\t\t\t\tOK\n");
}
