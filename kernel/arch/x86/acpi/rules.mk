acpi_objs += OsdEnvironment.o
acpi_objs += acpi_apm.o
acpi_objs += acpi_machdep.o
acpi_objs += acpi_wakeup.o
acpi_objs += madt.o
acpi_objs += srat.o

.obj/${config}/arch/x86/acpi/%.o:arch/x86/acpi/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $^

.obj/${config}/arch/x86/acpi/%.o:arch/x86/acpi/%.asm
	nasm -felf -o $@ $<

obj_dirs += .obj/${config}/arch/${gen_arch}/acpi
kern_objs += $(foreach x, ${acpi_objs}, .obj/${config}/arch/${gen_arch}/acpi/${x})
