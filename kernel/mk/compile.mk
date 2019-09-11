kern_cflags += -I. -std=gnu99 -O2
kern_cflags += -nostdinc -ffreestanding -nostdlib -fno-pie -fno-pic
kern_cflags += -DTK_VERSION="\"${VERSION}\"" -D_KERNEL
ifeq ($(origin NDEBUG), undefined)
kern_asflags += -gdwarf-2
kern_cflags += -MD -ggdb
endif

#ifeq ($(origin NoWerror), undefined)
#kern_cflags += -Werror
#endif

ifeq (x${CPU_X86},x1)
#
endif

ifeq (x${CPU_X86_64},x1)
kern_cflags += -mcmodel=large -mno-red-zone -mno-mmx -mno-sse -mno-sse2 
endif

kern_ldflags += -nodefaultlibs -nostdlibs -T${linker_script}
