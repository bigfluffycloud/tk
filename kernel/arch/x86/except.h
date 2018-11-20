#if	!defined(__machine_except_h)
#define	__machine_except_h
#include <type.h>
struct md_int_map {
  int	num;
  int	flags;
  char	*desc;
  void	(*hndlr)();
};
typedef struct md_int_map md_int_map;

struct md_trap_frame {
  uint32_t	ds,
                edi,
                esi,
                ebp,
                esp,
                ebx,
                edx,
                ecx,
                eax,
                int_no,
                err_code,
                eip,
                cs,
                eflags,
                user_esp,
                ss;
} __attribute__((__packed__));
typedef struct md_trap_frame md_trap_frame;

#define	INT_FAULT		0x0001
#define	INT_TRAP		0x0002
#define	INT_ABORT		0x0004
#define	INT_SYSCALL_COMPAT	0x0010		// Linux syscall wrapper
#define	INT_SYSCALL		0x0020		// Native syscall

// Mapping of interrupts to names and handlers
extern md_int_map md_int_tbl[];

#endif	// !defined(__machine_except_h)
