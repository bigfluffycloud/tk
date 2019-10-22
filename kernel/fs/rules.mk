#fs_objs += vfat.o

obj_dirs += .obj/${config}/fs
kern_objs += $(foreach x, ${fs_objs}, .obj/${config}/fs/${x})

.obj/${config}/fs/%.o:fs/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $<
