#include <core/cons.h>
#include <machine/reboot.h>

extern int md_init(void);
extern void init(void);

void	entry_multiboot(void *mb_info, unsigned int magic) {
  char *loader_name = (char *)((long *)mb_info)[16];
  if (magic != 0x2badb002) {
     cons_init();
     cons_write("*** Invalid loader magic, halting ***");
     md_halt();
  }

  // from core/init.c
  init();
}
