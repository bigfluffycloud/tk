ifeq (x${CF_ARCH},x)
$(error Must set CF_ARCH to a valid plaform, see arch/)
endif

# Sub-platform aliases
ifeq (${CF_ARCH},arm)
gen_arch := arm
endif

ifeq (${CF_ARCH},arm64)
gen_arch := arm
sub_arch := arm64
endif

ifeq (${CF_PLATFORM},rpi)
platform := rpi
endif

ifeq (${CF_ARCH},x86)
gen_arch := x86
sub_arch := 
endif

ifeq (${CF_ARCH},x64)
gen_arch := x86
sub_arch := x64
endif

ifeq ($(origin gen_arch), undefined)
$(error  gen_arch unset, bailing -- CF_ARCH: ${CF_ARCH})
endif

ifeq (arch/${gen_arch}/rules.mk, $(wildcard arch/${gen_arch}/rules.mk))
include arch/${gen_arch}/rules.mk
else
$(error !!! Invalid platform '${gen_arch}' selected !!!)
endif

kern_asflags += -I.
obj_dirs += .obj/${config}/arch/${gen_arch}
kern_objs += $(foreach x, ${arch_objs}, .obj/${config}/arch/${gen_arch}/${x})

.obj/${config}/arch/${gen_arch}/%.o:arch/${gen_arch}/%.S
	${kernel_cc} ${kern_asflags} -o $@ -c $<

.obj/${config}/arch/${gen_arch}/%.o:arch/${gen_arch}/%.c
	${kernel_cc} ${kern_cflags} -o $@ -c $<
