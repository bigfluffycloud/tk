#include <machine/gdt.h>
#include <machine/idt.h>
#include <machine/pic.h>
#include <cons.h>

int	md_init(void) {
  cons_init();
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write("popcorn OS/x86 starting\n");
  cons_colour(CONS_YELLOW, CONS_BLACK);
  cons_write("\n[");
  cons_colour(CONS_CYAN, CONS_BLACK);
  cons_write("machdep");
  cons_colour(CONS_YELLOW, CONS_BLACK);
  cons_write("]\n");
  md_pic_init();
  md_gdt_init();
  md_idt_init();
//  __asm__("int $0x3");
  return 0;
}
