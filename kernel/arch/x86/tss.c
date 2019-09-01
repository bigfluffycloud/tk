#include <sys/types.h>
#include <string.h>
#include <machine/tss.h>

static struct md_tss md_tss __attribute((aligned(4096)));
static char md_irq_stack[4096];

void md_tss_init(void) {
    memset(&md_tss, 0, sizeof(struct md_tss));
    md_tss.ss0 = 0x10;
    md_tss.bitmap = 0xdfff;
    memset(md_irq_stack, 0, sizeof(md_irq_stack));
}

struct md_tss *md_tss_get(void) {
    return &md_tss;
}

//void	md_tss_update(struct task *task) {
//    md_tss.esp0 = task->irq_stack_top;
//}

//uint64_t md_make_tss_desc(void *addr) {
//    return make_seg_desc((uint32_t)addr, 0x67, CLS_SYSTEM, 9, 0, GRAN_BYTE);
//}
