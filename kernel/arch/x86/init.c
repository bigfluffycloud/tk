#include <sys/types.h>
#include <machine/asm.h>
#include <machine/gdt.h>
#include <machine/idt.h>
#include <machine/pic.h>
#include <machine/pit.h>
#include <machine/mmu.h>
#include <machine/vmm.h>
#include <machine/task.h>
#include <cons.h>

int	md_init(void) {
  cons_init();
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write("tk version ");
  cons_colour(CONS_RED, CONS_BLACK);
  cons_write(TK_VERSION);
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" Copyright © 2019 osdev.ninja\n");
  cons_colour(CONS_YELLOW, CONS_BLACK);
  cons_write("\n[");
  cons_colour(CONS_CYAN, CONS_BLACK);
  cons_write("startup");
  cons_colour(CONS_YELLOW, CONS_BLACK);
  cons_write("]\n");
  // Disable interrupts
  // Configure interrupt controller
  md_pic_init();
  // Load Dummy IDT
  // Do nothing for a moment until interrupts settle
  __asm__ __volatile__("sti\nnop\nnop\nnop\nnop\nnop\ncli");
  // md_lapic_init();
  // md_ioapic_init();
  // Setup global descriptor table
  md_gdt_init();
  md_idt_init();
  md_pit_init();
  md_enable_interrupts();
  // Calculate speed
  // lapic_calculate_bus_speed();
//  printf("calculated speed bus speed: %ul0 hz", lapic_get_bus_speed);

   md_mmu_paging_init();
   md_vmm_init();
   md_task_init();
//  __asm__("int $0x80");
  return 0;
}
