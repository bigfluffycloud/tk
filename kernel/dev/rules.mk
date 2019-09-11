dev_objs += pcspkr.o
dev_objs += virtio_guest.o

obj_dirs += .obj/${config}/dev
kern_objs += $(foreach x, ${dev_objs}, .obj/${config}/dev/${x})

.obj/${config}/dev/%.o:dev/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $<
