#include <type.h>
#include <core/ssp.h>
#include <cons.h>
#include <machine/reboot.h>

void	init(void) {
  __stack_chkguard_setup();

  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("No init provided. Shutting down.\n");
  md_halt();
}
