#CC_PATH=/home/joseph/proj/toolchain/bin/

VERSION := "0.2.0-lite1"

all: world

# Configuration handling (XXX: Needs improved ;)
include mk/config.mk

# Subdirectories
include arch/rules.mk
include core/rules.mk
include crypto/rules.mk
include dev/rules.mk
include fonts/rules.mk
include fs/rules.mk
include ipc/rules.mk
include lib/rules.mk

# uIP based network stack
#include net/rules.mk

# Utilities
include mk/cross-compile.mk
include doc/rules.mk
include mk/compile.mk
include mk/kernel.mk
include mk/clean.mk
include mk/emu.mk

default_target ?= ${gzkern}

world: ${default_target}
