#if	!defined(__machine_mmu_h)
#define	__machine_mmu_h
#include <sys/stddef.h>
#include <sys/types.h>

// from ldscript
extern uint32_t __end;
extern uint32_t page_aligned_end;
extern uint32_t *page_directory;
extern void md_mmu_paging_init(void);

#endif	// !defined(__machine_mmu_h)
