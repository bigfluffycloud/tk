#include <sys/types.h>

struct md_tss {
    uint16_t	back_link, :16;
    void 	*esp0;
    uint16_t	ss0, :16;
    void	*esp1;
    uint16_t	ss1, :16;
    void	*esp2;
    uint16_t	ss2, :16;
    uint32_t	cr3;
    void	(*eip)(void);
    uint32_t	eflags;
    uint32_t	eax, ecx, edx, ebx;
    uint32_t	esp, ebp, esi, edi;
    uint16_t	es, :16;
    uint16_t	cs, :16;
    uint16_t	ss, :16;
    uint16_t	ds, :16;
    uint16_t	fs, :16;
    uint16_t	gs, :16;
    uint16_t	ldt, :16;
    uint16_t	trace, bitmap;
} __attribute__((packed));

//struct md_task;
extern struct md_tss *md_tss_get(void);
extern uint64_t td_make_tss_desc(void *);
// extern void md_tss_update(struct task *task);
extern void md_tss_init(void);
