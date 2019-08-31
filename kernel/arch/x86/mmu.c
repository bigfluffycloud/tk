#include <type.h>
#include <machine/asm.h>
#include <cons.h>

#define	PAGEDIR_ENTRIES	1024

extern uint32_t __end;

uint32_t page_aligned_end;
uint32_t *page_directory = NULL;

void md_mmu_paging_init(void) {
    int i = 0;

    page_aligned_end = (((uint32_t)__end) & 0xfffff000) + 0x1000;
    page_directory = (uint32_t *)page_aligned_end;
    for (i = 0; i < PAGEDIR_ENTRIES; i++) {
       // attribute: supervisor level, read/write, not present.
       page_directory[i] = 0 | 2;
    }
}

static inline void md_flush_tlb_single(unsigned long addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

