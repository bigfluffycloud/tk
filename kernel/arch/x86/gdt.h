#if	!defined(__machine_gdt_h)
#define	__machine_gdt_h
#include <type.h>

struct	md_gdt_entry {
  uint16_t	limit_low;	// lower 16 bits of limit
  uint16_t	base_low;	// lower 16 bits of base
  uint8_t	base_mid;	// middle 8 bits of base
  uint8_t	access;		// access flags
  uint8_t	granularity;
  uint8_t	base_hi;	// top 8 bits of base
} __attribute__((__packed__));
typedef	struct md_gdt_entry md_gdt_entry;

struct	md_gdt_ptr {
  uint16_t	limit;		// upper 16 bits of all limits
  uint32_t	base;		// base address of first entry
} __attribute__((__packed__));
typedef struct md_gdt_ptr md_gdt_ptr;

extern	void	md_gdt_init(void);
extern	void	md_gdt_flush(uint32_t ptr);	// locore.S
extern	void	md_gdt_set(int32_t num, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);

#endif	// !defined(__machine_gdt_h)
