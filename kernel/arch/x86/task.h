#if	!defined(__machine_task_h)
#define	__machine_task_h

typedef struct Task Task;

// task machdep code
extern int md_task_init(Task *tp);

#endif	// !defined(__machine_task_h)
