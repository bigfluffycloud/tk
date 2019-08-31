#include <type.h>
#include <core/task.h>
#include <machine/task.h>
int task_init(void) {
    md_task_init();
    return 0;
}