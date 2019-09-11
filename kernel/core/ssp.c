#include <machine/reboot.h>
#include <core/cons.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <lib/arc4random.h>

long __stack_chk_guard[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };

void __stack_chk_fail(void) {
  cons_clear();
  cons_write("ERROR: Stack corrupted, halting system\n");
  md_halt();
}

#define __arraycount(__x)	(sizeof(__x) / sizeof(__x[0]))
void __stack_chkguard_setup(void) {
  size_t i;
  long guard[__arraycount(__stack_chk_guard)];

  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("*");
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" kernel stack guard");

  memset(guard, sizeof(guard), 0);
  // XXX: Fix arc4rand!
//  arc4rand(guard, sizeof(guard), 0);

  for (i = 0; i < __arraycount(guard); i++)
     __stack_chk_guard[i] = guard[i];

  cons_colour(CONS_GREEN, CONS_BLACK);
  cons_write("\t\t\tOK\n");
}
