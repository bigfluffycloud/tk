clean:
	${RM} ${clean_extra} ${kern_objs} ${vmkern} ${gzkern}
	${RM} machine

distclean: clean
	${RM} -r .obj .config bochsrc.txt bochsout.txt
