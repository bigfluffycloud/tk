#include <sys/types.h>
#include <core/cons.h>
#include <machine/mmu.h>
#include <machine/vmm.h>

#if	0
static pageframe_t kalloc_frame_int(void) {
      uint32_t i = 0;
      while (frame_map[i] != FREE) {
           i++;
           if (i == npages) {
              return(ERROR);
           }
       }
       frame_map[i] = USED;
       return(startframe + (i * 0x1000));
       //return the address of the page frame based on the location declared free in the array
}

pageframe_t kalloc_frame(void) {
        static uint8_t allocate = 1;//whether or not we are going to allocate a new set of preframes
        static uint8_t pframe = 0;
        pageframe_t ret;
 
        if (pframe == 20) {
           allocate = 1;
        }
 
        if (allocate == 1) {
           for (int i = 0; i<20; i++)
               pre_frames[i] = kalloc_frame_int();
           pframe = 0;
           allocate = 0;
        }

        ret = pre_frames[pframe];
        pframe++;
        return(ret);
}

void kfree_frame(pageframe_t a) {
        a = a - startframe;	// get the offset from the first frame
        if (a == 0) { 		// in case it is the first frame we are freeing
           uint32_t index = (uint32_t)a;
           frame_map[index] = FREE;
        } else {
           a = a;//divide by 4kb to get the index to declare free
           uint32_t index = ((uint32_t)a)/0x1000;
           frame_map[index] = FREE;
        }
}

#endif	// 0

void md_vmm_init(void) {
  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("*");
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" setup VMM");

  // Do stuff
  cons_colour(CONS_GREEN, CONS_BLACK);
  cons_write("\t\t\t\tOK\n");
}
