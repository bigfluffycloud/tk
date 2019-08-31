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
