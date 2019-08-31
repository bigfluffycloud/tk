kern_cpp_objs += $($CC ${kern_cflags} -print-file-name=crtbegin.o)
kern_cpp_objs += $($CC ${kern_cflags} -print-file-name=crtend.o)

${gzkern}: ${vmkern}
	@echo "*** Compressing kernel image ${gzkern}..."
	cat $< | gzip -9 > $@

${vmkern}: prebuild ${kern_objs}
	@echo "*** Linking ${vmkern} ..."
	${LD} ${kern_ldflags} -o $@ ${kern_objs} ${kern_cpp_objs}

	@if grub-file --is-x86-multiboot $@; then \
  		echo "Multiboot image OK"; \
	else \
		echo "NOT multiboot"; \
	fi

prebuild:
	@echo "*** Preparing target tree..."
	mkdir -p ${obj_dirs}
	-[ -h machine ] && rm -f machine
	ln -s arch/${gen_arch} machine
	@echo "*** Building ${vmkern} ..."
