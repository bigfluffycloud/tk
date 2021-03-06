#include <sys/types.h>
#include <core/task.h>
#include <machine/task.h>

int md_task_init(Task *tp) {
#if	defined(CPU_X86)
    // Get EFLAGS and CR3
    asm volatile("movl %%cr3, %%eax; movl %%eax, %0;":"=m"(tp->regs.cr3)::"%eax");
    asm volatile("pushfl; movl (%%esp), %%eax; movl %%eax, %0; popfl;":"=m"(tp->regs.eflags)::"%eax");
#endif	// defined(CPU_X86)

    return 0;
}
