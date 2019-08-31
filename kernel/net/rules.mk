net_objs += clock-arch.o
net_objs += memb.o
net_objs += psock.o
net_objs += tapdev.o
net_objs += test.o
net_objs += timer.o
net_objs += uip-fw.o
net_objs += uip-neighbor.o
net_objs += uip-split.o
net_objs += uip.o
net_objs += uip_arp.o
net_objs += uiplib.o

obj_dirs += .obj/${config}/net
kern_objs += $(foreach x, ${net_objs}, .obj/${config}/net/${x})

.obj/${config}/net/%.o:net/%.c
	${CC} ${kern_cflags} -o $@ -c $<
