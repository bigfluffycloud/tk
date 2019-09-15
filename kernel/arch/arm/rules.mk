#kern_asflags +=
#kern_cflags +=
linker_script := machine/vmkern.ld

############

#arch_objs +=

.obj/${config}/arch/x86/%.o:arch/x86/%.asm
	nasm -felf -o $@ $<
