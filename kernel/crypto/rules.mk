#crypto_objs += arc4random.o

obj_dirs += .obj/${config}/crypto
kern_objs += $(foreach x, ${crypto_objs}, .obj/${config}/crypto/${x})

.obj/${config}/crypto/%.o:crypto/%.c
	${CC} ${kern_cflags} -o $@ -c $<
