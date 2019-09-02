ifeq (x${CPU_X86},x1)
kern_asflags += -m32
kern_cflags += -m32
linker_script := machine/vmkern.ld
endif

ifeq (x${CPU_X86_64},x1)
kern_asflags += -m64
kern_cflags += -m64
linker_script := machine/vmkern64.ld
endif

# multiboot.o *MUST* come first!
# C objects
arch_objs += multiboot.o
#arch_objs += cmos.o
arch_objs += cons_vga.o
arch_objs += except.o
arch_objs += font_vga.o
arch_objs += gdt.o
#arch_objs += idler.o
arch_objs += idt.o
arch_objs += init.o
arch_objs += isr.o
#arch_objs += lapic.o
arch_objs += locore.o
arch_objs += mb_entry.o
arch_objs += mmu.o
arch_objs += nmi.o
arch_objs += pae.o
arch_objs += pic.o
arch_objs += pit.o
arch_objs += ps2.o
arch_objs += reboot.o
arch_objs += rtc.o
arch_objs += serio.o
arch_objs += sse.o
arch_objs += sse_asm.o
arch_objs += task.o
arch_objs += tss.o
arch_objs += vga.o
arch_objs += virt.o
arch_objs += vmm.o

# Assembler objects
arch_objs += crti.o
arch_objs += crtn.o

.obj/${config}/arch/x86/%.o:arch/x86/%.asm
	nasm -felf -o $@ $<
