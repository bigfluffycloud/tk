obj_dirs += fonts

.obj/fonts/%.elf: fonts/%.psf
	@echo "Converting PSF font $^ to ELF font $@..."
	objcopy -O elf64-x86-64 -B i386 -I binary $^ $@
	readelf -s $@
