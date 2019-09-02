subdirs := lib kernel

include lib/rules.mk
all world clean distclean install image qemu bochs:
	@for i in ${subdirs}; do \
		${MAKE} -C $$i $@; \
	done
