floppy: .obj/${config}/floppy.img 

ifeq (${loader}, grub)
ifeq (/usr/share/grub/stage1, $(wildcard /usr/share/grub/stage1))
grub_dir := /usr/share/grub/
endif

ifeq (/usr/lib/grub/i386-pc/stage1, $(wildcard /usr/lib/grub/i386-pc/stage1))
grub_dir := /usr/lib/grub/i386-pc/
endif
endif

ifeq (/usr/share/syslinux/mboot.c32, $(wildcard /usr/share/syslinux/mboot.c32))
syslinux_dir := /usr/share/syslinux/
endif

ifeq (/usr/lib/syslinux/mboot.c32, $(wildcard /usr/lib/syslinux/mboot.c32))
syslinux_dir := /usr/lib/syslinux
endif

ifeq (/usr/lib/syslinux/modules/bios/mboot.c32, $(wildcard /usr/lib/syslinux/modules/bios/mboot.c32))
syslinux_dir = /usr/lib/syslinux/modules/bios
endif

floppy := .obj/${config}/floppy.img
${floppy}: ${gzkern}
	sudo dd if=/dev/zero of=${floppy} bs=512 count=2880
	sudo mkfs.vfat ${floppy}
	sudo mmd -i ${floppy} boot
	sudo mcopy -i ${floppy} ${gzkern} ::
ifeq (${loader}, syslinux)
	sudo syslinux ${floppy}
	sudo mcopy -n -i ${floppy} ${syslinux_dir}/*.c32 ::
	echo "TIMEOUT 1" > .obj/${config}/syslinux.cfg
	echo "DEFAULT mboot.c32 vmkern.gz ${kern_args}" >> .obj/${config}/syslinux.cfg
	sudo mcopy -i ${floppy} .obj/${config}/syslinux.cfg ::
endif
ifeq (${loader}, grub)
	sudo mmd -i ${floppy} boot/grub
	sudo mcopy -i ${floppy} arch/${gen_arch}/menu.lst ::boot/grub
	sudo mcopy -i ${floppy} ${grub_dir}/{fat_stage1_5,stage{1,2}} ::boot/grub
	echo "(fd0) ${floppy}" > .obj/${config}/grub.map
	echo "root (fd0)" > .obj/${config}/grub.script
	echo "setup (fd0)" >> .obj/${config}/grub.script
	sudo grub --no-floppy --device-map=.obj/${config}/grub.map < .obj/${config}/grub.script
endif

ifneq ($(origin EMU_SMP_CPUS), undefined)
qemu_opts += -smp ${EMU_SMP_CPUS}
endif
ifeq ($(origin NDEBUG), undefined)
qemu_gdb_port := $(shell expr `id -u` % 5000 + 25000)
qemu_opts += -gdb tcp::${qemu_gdb_port}
endif
#qemu_opts += -echr 2 -nographic -curses -serial mon:stdio

qemu: floppy
ifneq (x${qemu_gdb_port}, x)
	@echo "Using tcp::${qemu_gdb_port} for gdb port"
endif
	qemu-system-i386 -fda ${floppy} ${qemu_opts}

bochs: floppy bochsrc.txt
	bochs

bochsrc.txt:
	echo "boot: floppy" > bochsrc.txt
	echo "floppya: type=1_44, 1_44=\"${floppy}\", status=inserted" >> bochsrc.txt
	echo "cpu: count=1, ips=500000, reset_on_triple_fault=0, ignore_bad_msrs=1" >> bochsrc.txt
	echo "log: bochsout.txt" >> bochsrc.txt
	echo "mouse: enabled=0" >> bochsrc.txt
	echo "clock: sync=realtime" >> bochsrc.txt
