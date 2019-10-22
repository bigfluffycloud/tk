kernel_cc := ${CC_PATH}${tc_prefix}gcc
kernel_ld := ${CC_PATH}${tc_prefix}ld
kernel_as := ${CC_PATH}${tc_prefix}gcc
kernel_nm := ${CC_PATH}${tc_prefix}nm

kern_cflags += -I. -std=gnu11 -O2
kern_cflags += -nostdinc -ffreestanding -nostdlib -fno-pie -fno-pic
kern_cflags += -DTK_VERSION="\"${VERSION}\"" -D_KERNEL

ifeq ($(origin NDEBUG), undefined)
kern_asflags += -gdwarf-2
kern_cflags += -MD -ggdb
endif

ifeq ($(origin NoWerror), undefined)
kern_cflags += -Werror
endif

kern_ldflags += -nodefaultlibs -nostdlibs -T${linker_script}
