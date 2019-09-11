#include <sys/types.h>
#include <core/cons.h>
#include <machine/gdt.h>
#include <machine/tss.h>
md_gdt_entry md_gdt_entries[5];
md_gdt_ptr md_gdtptr;

void	md_gdt_set(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
  // Some error checking, tho we should probably treat this as fatal, we do not...
  if (limit > 65536 && (limit & 0xfff) != 0xfff) {
     cons_colour(CONS_RED, CONS_WHITE);
     cons_write("ERROR: Invalid md_gdt_set limit");
     cons_colour(CONS_WHITE, CONS_RED);
     cons_printf("Invalid limit %lu @ %s:%D\n", __FUNCTION__, __LINE__);
     return;
  }

  md_gdt_entries[num].base_low =  (base & 0xffff);
  md_gdt_entries[num].base_mid =  (base >> 16) & 0xff;
  md_gdt_entries[num].base_hi =   (base >> 24) & 0xff;

  md_gdt_entries[num].limit_low = (limit & 0xffff);

  md_gdt_entries[num].granularity |= gran & 0xf0;
  md_gdt_entries[num].access = access;
}

void	md_gdt_init(void) {
  cons_colour(CONS_RED, CONS_BLACK);
  cons_write("*");
  cons_colour(CONS_LTGREY, CONS_BLACK);
  cons_write(" setup GDT");

  md_gdtptr.limit = (sizeof(md_gdt_entry) * 5) - 1;
  md_gdtptr.base = (uint32_t)&md_gdt_entries;

  // 	   num, base,   limit,         access,  gran
  md_gdt_set(0,	0,	0,		0,	0);	// NULL
  md_gdt_set(1, 0,	0xffffffff,	0x9a,	0xcf);	// Kernel:code
  md_gdt_set(2,	0,	0xffffffff,	0x92,	0xcf);	// Kernel:data
  md_gdt_set(3,	0,	0xffffffff,	0xfa,	0xcf);	// App:code
  md_gdt_set(4,	0,	0xffffffff,	0xf2,	0xcf);	// App:data

// XXX: Fix TSS code and reenable
//  md_tss_write(5, 0x10, 0x0);
  md_gdt_flush((uint32_t)&md_gdtptr);
//  md_tss_flush();

  cons_colour(CONS_GREEN, CONS_BLACK);
  cons_write("\t\t\t\tOK\n");
}
