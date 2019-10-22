//
// machine/mb_entry.c: x86{,_64} multiboot (2) loader support
//
#include <core/cons.h>
#include <machine/reboot.h>

extern int md_init(void);
extern void init(void);

/*
 * entry_multiboot:
 * 	Returns: nothing
 *	Arguments:
 *		Pointer to multiboot info struct from loaer
 *		Unsigned int - load magic
 */
void	entry_multiboot(void *mb_info, unsigned int magic) {
  char *loader_name = (char *)((long *)mb_info)[16];

  // Check for GRUB boot signature to be correct
  if (magic != 0x2badb002) {
     cons_init();
     cons_write("*** Invalid multiboot magic from loader, halting ***");
     md_halt();
  }

  // from core/init.c
  init();
}
