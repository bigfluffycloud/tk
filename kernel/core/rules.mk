core_objs += debug.o
core_objs += init.o
core_objs += interrupt.o
core_objs += ssp.o
core_objs += cons.o
core_objs += task.o
core_objs += timer.o
core_objs += vmm.o
#core_objs += elf.o

obj_dirs += .obj/${config}/core
kern_objs += $(foreach x, ${core_objs}, .obj/${config}/core/${x})

.obj/${config}/core/%.o:core/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $<
