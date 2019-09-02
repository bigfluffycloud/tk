all: world

SUDO := $(shell which sudo)

help:
	@echo "Hello! This folder contains all our GPL licensed external friends."
	@echo "This should help ease compliance and ensure everyone has a good time!"
	@echo "sudo is ${SUDO}"

GNU_MIRROR ?= https://ftp.gnu.org/gnu
gcc_ver ?= 9.2.0
gcc_url := ${GNU_MIRROR}/gcc/gcc-${gcc_ver}/gcc-${gcc_ver}.tar.xz
binutils_ver ?= 2.32
binutils_url := ${GNU_MIRROR}/binutils/binutils-${binutils_ver}.tar.xz

include toolchain/rules.mk

deb_deps:
	${SUDO} apt install ${deb_deps}

fetch:
	[ -f cache/gcc-${gcc_ver}.tar.xz ] || (cd cache; wget ${gcc_url})
	[ -f cache/gcc-${gcc_ver}.tar.xz.sig ] || (cd cache; wget ${gcc_url}.sig)
	[ -f cache/binutils-${binutils_ver}.tar.xz ] || (cd cache; wget ${binutils_url})
	[ -f cache/binutils-${binutils_ver}.tar.xz.sig ] || (cd cache; wget ${binutils_url}.sig)

automaton: deb_deps fetch

world: automaton binutils gcc
