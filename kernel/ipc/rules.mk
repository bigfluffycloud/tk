#ipc_objs += mailbox.o

obj_dirs += .obj/${config}/ipc
kern_objs += $(foreach x, ${ipc_objs}, .obj/${config}/ipc/${x})

.obj/${config}/ipc/%.o:ipc/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $<
