#include <sys/stddef.h>
#include <sys/types.h>
#include <machine/asm.h>
#include <machine/virt.h>

#if	0
void md_vmxon(void) {
     uint32_t * region = (uint32_t *)allocate_4k_aligned(4096);
     uint64_t region64 = (uint64_t)((size_t)(region) & 0xFFFFFFFF);
     asm volatile("  vmxon %0; "::"m" (region64));
}

void md_vmcs(void) {
     asm volatile ("vmptrld %0; ":: "m" (vmcsRegion64));
}
#endif
