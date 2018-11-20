${gzkern}: ${vmkern}
	@echo "*** Compressing kernel image ${gzkern}..."
	cat $< | gzip -9 > $@

${vmkern}: prebuild ${kern_objs}
	@echo "*** Linking ${vmkern} ..."
	${LD} ${kern_ldflags} -o $@ ${kern_objs}

prebuild:
	@echo "*** Preparing target tree..."
	mkdir -p ${obj_dirs}
	-[ -h machine ] && rm -f machine
	ln -s arch/${gen_arch} machine
	@echo "*** Building ${vmkern} ..."
