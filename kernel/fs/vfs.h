#if	!defined(__fs_vfs_h)
#define	__fs_vfs_h

#include <types.h>

struct	vfs_op {
};
typedef struct vfs_op vfs_op;

struct	drv_vfs {
  // [global] is for the driver, <instance> is this mount
  int		refcnt;

  // file operations
  int		op_open(vfs_op *p);
  int		op_close(vfs_op *p);
  size_t	op_read(vfs_op *p);
  size_t	op_write(vfs_op *p);
};

#endif	// !defined(__fs_vfs_h)
