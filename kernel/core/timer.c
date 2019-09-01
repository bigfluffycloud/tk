#include <sys/types.h>
#include <ipc/msg.h>
#include <core/timer.h>

struct TimerBlock timerblocks[MAX_TIMERS];

void timer_check_notify(void) {
     uint8_t i;

     for (i = 0; i < MAX_TIMERS; i++) {
         if (timerblocks[i].CountDown > 0) {
            timerblocks[i].CountDown--;

            if (timerblocks[i].CountDown == 0) {
//               ipc_msg(timerblocks[i].task, IPCMSG_TIMER);
               timerblocks[i].task = (task_t *)NULL;
            }
         }
    }
}

struct TimerBlock *timer_block_find(void) {
     uint8_t i;

     for (i = 0; i < MAX_TIMERS; i++)
         if (timerblocks[i].CountDown == 0 && timerblocks[i].task == NULL)
            return &timerblocks[i];

     return NULL;
}

void sleep(uint32_t delay) {
     struct TimerBlock *t;

     if ((t = timer_block_find()) == NULL)
        return;

     t->CountDown = delay;
//     t->e = task_get();
//     ipc_msg_wait(t->e);
}
