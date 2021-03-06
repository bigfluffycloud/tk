#if	!defined(__machine_asm_h)
#define	__machine_asm_h

#include <sys/types.h>
#include <sys/stdint.h>
#include <sys/stdbool.h>
static inline void	md_outb(uint16_t port, uint8_t val) {
  asm volatile ("outb %1, %0" :: "dN" (port), "a" (val));
}

static inline void	md_outw(uint16_t port, uint16_t val) {
  asm volatile ("outw %1, %0" :: "dN" (port), "a" (val));
}

static inline uint8_t	md_inb(uint16_t port) {
  uint8_t ret;
  asm volatile ("inb %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

static inline uint16_t md_inw(uint16_t port) {
  uint16_t ret;
  asm volatile ("inw %1, %0" : "=a" (ret) : "dN" (port));
  return ret;
}

static inline uint32_t md_inl(uint16_t port) {
  uint32_t ret;
  asm volatile("in %d0, %w1" : "=a"(ret) : "dN"(port));
  return ret;
}

static inline void md_flush_tlb_single(unsigned long addr) {
   asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
}

static inline void md_enable_interrupts(void) {
   asm volatile("sti");
}

static inline void md_disable_interrupts(void) {
   asm volatile("cli");
}

static inline bool are_interrupts_enabled(void) {
    unsigned long flags;
    asm volatile ( "pushf\n\t"
                   "pop %0"
                   : "=g"(flags) );
    return flags & (1 << 9);
}

static inline uint32_t farpeekl(uint16_t sel, void* off) {
    uint32_t ret;
    asm ( "push %%fs\n\t"
          "mov  %1, %%fs\n\t"
          "mov  %%fs:(%2), %0\n\t"
          "pop  %%fs"
          : "=r"(ret) : "g"(sel), "r"(off) );
    return ret;
}

static inline void farpokeb(uint16_t sel, void* off, uint8_t v) {
    asm ( "push %%fs\n\t"
          "mov  %0, %%fs\n\t"
          "movb %2, %%fs:(%1)\n\t"
          "pop %%fs"
          : : "g"(sel), "r"(off), "r"(v) );
    /* TODO: Should "memory" be in the clobber list here? */
}

static inline void md_io_wait(void) {
    /* TODO: This is probably fragile. */
    asm volatile ( "jmp 1f\n\t"
                   "1:jmp 2f\n\t"
                   "2:" );
}

static inline void md_io_wait2(void) {
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    asm volatile ( "outb %%al, $0x80" : : "a"(0) );
    /* %%al instead of %0 makes no difference.  TODO: does the register need to be zeroed? */
}

static inline unsigned long md_save_irqdisable(void) {
    unsigned long flags;
    asm volatile ("pushf\n\tcli\n\tpop %0" : "=r"(flags) : : "memory");
}
 
static inline void md_irqrestore(unsigned long flags) {
    asm ("push %0\n\tpopf" : : "rm"(flags) : "memory","cc");
}
 
//static void intended_usage(void) {
//    unsigned long f = save_irqdisable();
//    do_whatever_without_irqs();
//    irqrestore(f);
//}

static inline void md_lidt(void* base, uint16_t size) {
    // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        void*    base;
    } __attribute__((packed)) IDTR = { size, base };
 
    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

/* GCC has a <cpuid.h> header you should use instead of this. */
static inline void cpuid(int code, uint32_t* a, uint32_t* d) {
    asm volatile ( "cpuid" : "=a"(*a), "=d"(*d) : "0"(code) : "ebx", "ecx" );
}

#if	defined(CPU_X86)
static inline uint64_t md_rdtsc(void) {
    uint64_t ret;
    asm volatile ( "rdtsc" : "=A"(ret) );
    return ret;
}

static inline void wrmsr(uint32_t msr_id, uint64_t msr_value) {
    asm volatile ( "wrmsr" : : "c" (msr_id), "A" (msr_value) );
}

static inline uint64_t rdmsr(uint32_t msr_id) {
    uint64_t msr_value;
    asm volatile ( "rdmsr" : "=A" (msr_value) : "c" (msr_id) );
    return msr_value;
}
#endif	// defined(CPU_X86)

#if	defined(CPU_X86_64)
uint64_t md_rdtsc(void) {
    uint32_t low, high;
    asm volatile("rdtsc":"=a"(low),"=d"(high));
    return ((uint64_t)high << 32) | low;
}

static inline void wrmsr(uint64_t msr, uint64_t value) {
	uint32_t low = value & 0xFFFFFFFF;
	uint32_t high = value >> 32;
	asm volatile (
		"wrmsr"
		:
		: "c"(msr), "a"(low), "d"(high)
	);
}

static inline uint64_t rdmsr(uint64_t msr) {
	uint32_t low, high;
	asm volatile (
		"rdmsr"
		: "=a"(low), "=d"(high)
		: "c"(msr)
	);
	return ((uint64_t)high << 32) | low;
}
#endif	// defined(CPU_X86_64)

static inline unsigned long read_cr0(void) {
    unsigned long val;
    asm volatile ( "mov %%cr0, %0" : "=r"(val) );
    return val;
}

static inline void invlpg(void* m) {
    /* Clobber memory to avoid optimizer re-ordering access before invlpg, which may cause nasty bugs. */
    asm volatile ( "invlpg (%0)" : : "b"(m) : "memory" );
}


#endif	// !defined(__machine_asm_h)
