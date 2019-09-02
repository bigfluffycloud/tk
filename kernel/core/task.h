#if	!defined(__core_task_h)
#define	__core_task_h

struct task {
    uint32_t pid;
};

typedef struct task task_t;

extern void task_init(void);
 
typedef struct {
    uint32_t eax, ebx, ecx, edx, esi, edi, esp, ebp, eip, eflags, cr3;
} Registers;
 
typedef struct Task {
    Registers regs;
    struct Task *next;
} Task;
 
extern void task_initTasking();
extern void task_create(Task*, void(*)(), uint32_t, uint32_t*);
 
extern void yield(); // Switch task frontend
extern void task_switch(Registers *from, Registers *to);
 
#endif	// !defined(__core_task_h)
