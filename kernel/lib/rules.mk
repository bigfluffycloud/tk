#lib_objs += arc4random.o
lib_objs += atoi.o
lib_objs += memset.o
lib_objs += memmove.o
lib_objs += random.o
obj_dirs += .obj/${config}/lib
kern_objs += $(foreach x, ${lib_objs}, .obj/${config}/lib/${x})

.obj/${config}/lib/%.o:lib/%.c
	${CC} ${kern_cflags} -o $@ -c $<
