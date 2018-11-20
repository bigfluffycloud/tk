kern_cflags += -I. -std=gnu99 -O2
kern_cflags += -nostdinc -ffreestanding
kern_cflags += -fstack-protector-all
kern_cflags += -Wall -Wno-unused -pedantic

ifeq ($(origin NDEBUG), undefined)
kern_asflags += -gdwarf-2
kern_cflags += -MD -ggdb
endif

ifeq ($(origin NoWerror), undefined)
kern_cflags += -Werror
endif

kern_ldflags += -nodefaultlibs -nostdlibs -T${linker_script}