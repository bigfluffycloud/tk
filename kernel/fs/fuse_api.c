// Here we provide the kernel side of userspace file systems
//
// To gain the benefit of the large number of FUSE based file systems,
// we try to behave a similarly to fuse kernel module on Linux.
//
// The goal is for userspace to use an unmodified libfuse library
//
//

#include "vfs.h"
#include "fuse_api.h"
