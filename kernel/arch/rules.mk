ifeq (x${CF_ARCH}, x)
$(error Must set CF_ARCH to a valid plaform, see arch/)
endif

# Sub-platform aliases
ifeq (${CF_ARCH}, x64})
gen_arch := x86
sub_arch := x64
endif

# Hasn't been overriden, so set to config arch
gen_arch ?= ${CF_ARCH}

ifeq (arch/${gen_arch}/rules.mk, $(wildcard arch/${gen_arch}/rules.mk))
include arch/${gen_arch}/rules.mk
else
$(error !!! Invalid platform '${gen_arch}' selected !!!)
endif

obj_dirs += .obj/${config}/arch/${gen_arch}
kern_objs += $(foreach x, ${arch_objs}, .obj/${config}/arch/${gen_arch}/${x})

.obj/${config}/arch/${gen_arch}/%.o:arch/${gen_arch}/%.S
	${kernel_cc} ${kern_asflags} -o $@ -c $<

.obj/${config}/arch/${gen_arch}/%.o:arch/${gen_arch}/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $<
