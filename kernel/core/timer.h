#if	!defined(__core_timer_h)
#define	__core_timer_h
#include <sys/types.h>
#include <ipc/msg.h>
#include <core/task.h>

#define	MAX_TIMERS		20

struct TimerBlock {
     task_t *task;
     uint32_t CountDown;
};

extern struct TimerBlock timerblocks[MAX_TIMERS];
extern void timer_check_notify(void);

#endif	// !defined(__core_timer_h)
