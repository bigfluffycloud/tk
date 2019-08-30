core_objs += init.o
core_objs += ssp.o
core_objs += cons.o

obj_dirs += .obj/${config}/core
kern_objs += $(foreach x, ${core_objs}, .obj/${config}/core/${x})

.obj/${config}/core/%.o:core/%.c
	${CC} ${kern_cflags} -o $@ -c $<
