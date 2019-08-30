#include <type.h>

void md_idler(void) {
    do {
        md_task_current->state = TASK_SLEEPING;
        scheduler_run();
        asm("sti; hlt; cli");
    } while (md_task_current->state == TASK_RUNNING);
}
