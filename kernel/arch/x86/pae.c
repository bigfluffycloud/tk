#include <sys/stddef.h>
#include <sys/types.h>
#include <core/cons.h>
#include <machine/asm.h>
#include <machine/pae.h>
uint64_t page_dir_ptr_tab[4] __attribute__((aligned(0x20)));
// 512 entries
uint64_t page_dir[512] __attribute__((aligned(0x1000)));  // must be aligned to page boundary
uint64_t page_tab[512] __attribute__((aligned(0x1000)));

void md_pae_init(void) {
     unsigned int i, address = 0;
     uint64_t *page_dir;
     page_dir_ptr_tab[0] = (uint64_t)&page_dir | 1; // set the page directory into the PDPT and mark it present
     page_dir[0] = (uint64_t)&page_tab | 3; //set the page table into the PD and mark it present/writable

     cons_colour(CONS_RED, CONS_BLACK);
     cons_write("*");
     cons_colour(CONS_LTGREY, CONS_BLACK);
     cons_write(" setup PAE");

     for (i = 0; i < 512; i++) {
         page_tab[i] = address | 3; // map address and mark it present/writable
         address = address + 0x1000;
     }

#if	defined(CPU_X86)
     asm volatile ("movl %cr4, %eax; bts $5, %eax; movl %eax, %cr4"); // set bit5 in CR4 to enable PAE		 
     asm volatile ("movl %%eax, %%cr3" :: "a" (&page_dir_ptr_tab)); // load PDPT into CR3
     asm volatile ("movl %cr0, %eax; orl $0x80000000, %eax; movl %eax, %cr0;");
#endif
#if	defined(CPU_X86_64)
     // XXX: make 64bit version
#endif
     page_dir = (uint64_t*)page_dir_ptr_tab[3]; // get the page directory (you should 'and' the flags away)
     page_dir[511] = (uint64_t)page_dir; // map pd to itself
     page_dir[510] = page_dir_ptr_tab[2]; // map pd3 to it
     page_dir[509] = page_dir_ptr_tab[1]; // map pd2 to it
     page_dir[508] = page_dir_ptr_tab[0]; // map pd1 to it
     page_dir[507] = (uint64_t)&page_dir_ptr_tab; /* map the PDPT to the directory */

     cons_colour(CONS_GREEN, CONS_BLACK);
     cons_write("\t\t\t\tOK\n");

}
