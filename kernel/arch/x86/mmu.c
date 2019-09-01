#include <sys/stddef.h>
#include <sys/types.h>
#include <machine/asm.h>
#include <machine/mmu.h>
#include <cons.h>

#define	PAGEDIR_ENTRIES	1024

extern uint32_t __end;

uint32_t page_aligned_end;
uint32_t *page_directory = NULL;

void md_mmu_paging_init(void) {
    int i = 0;

    cons_colour(CONS_RED, CONS_BLACK);
    cons_write("*");
    cons_colour(CONS_LTGREY, CONS_BLACK);
    cons_write(" setup MMU");
    page_aligned_end = (((uint32_t)__end) & 0xfffff000) + 0x1000;
    page_directory = (uint32_t *)page_aligned_end;

    for (i = 0; i < PAGEDIR_ENTRIES; i++) {
       // attribute: supervisor level, read/write, not present.
       page_directory[i] = 0 | 2;
    }

    cons_colour(CONS_GREEN, CONS_BLACK);
    cons_write("\t\t\t\tOK\n");
}
