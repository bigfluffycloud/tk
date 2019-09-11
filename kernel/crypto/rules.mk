#crypto_objs += arc4random.o

obj_dirs += .obj/${config}/crypto
kern_objs += $(foreach x, ${crypto_objs}, .obj/${config}/crypto/${x})

.obj/${config}/crypto/%.o:crypto/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $<
