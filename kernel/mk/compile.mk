kern_cflags += -I. -std=gnu99 -O2
kern_cflags += -nostdinc -ffreestanding -nostdlib -fno-pie -fno-pic

ifeq ($(origin NDEBUG), undefined)
kern_asflags += -gdwarf-2
kern_cflags += -MD -ggdb
endif

ifeq ($(origin NoWerror), undefined)
kern_cflags += -Werror
endif

kern_ldflags += -nodefaultlibs -nostdlibs -T${linker_script}
