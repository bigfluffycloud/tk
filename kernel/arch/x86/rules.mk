linker_script := machine/vmkern.ld
kern_asflags += -m32
kern_cflags += -m32

# multiboot.o *MUST* come first!
arch_objs += multiboot.o
arch_objs += cons_vga.o
arch_objs += except.o
arch_objs += gdt.o
arch_objs += idt.o
arch_objs += init.o
#arch_objs += idler.o
arch_objs += isr.o
arch_objs += locore.o
arch_objs += mb_entry.o
arch_objs += mmu.o
arch_objs += reboot.o
arch_objs += pic.o
arch_objs += pit.o
arch_objs += task.o
arch_objs += tss.o
arch_objs += vga.o

.obj/${config}/arch/x86/%.o:arch/x86/%.asm
	nasm -felf -o $@ $<
