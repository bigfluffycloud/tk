#include <sys/types.h>
#include <core/ssp.h>
#include <core/cons.h>
#include <core/vmm.h>
#include <machine/reboot.h>
#include <config.h>
#include <core/configtest.h>

// We are called by the platform boot entry code
// this is in machine/mb_entry.c on x86...
void	init(void) {
  // Platform setup
  md_init();
  // Memory manager setup
  vmm_init();

  // Enable stack protection
  __stack_chkguard_setup();

  // Provide notice that no init was passed
  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("No initfs provided. Shutting down.\n");

  // -- Halt the machine since we cannot do anything with initfs
  md_halt();
}
