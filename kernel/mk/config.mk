config ?= .config

ifeq (${config}, $(wildcard ${config}))
include ${config}
else
$(warning Config ${config} not found, using .config.default)
$(shell cp -i .config.default .config)
config = .config
include ${config}
endif

vmkern ?= .obj/${config}/vmkern
gzkern ?= ${vmkern}.gz

CPU_X86_64=1
#CPU_X86=1
