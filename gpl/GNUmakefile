
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
libiconv_ver ?= 1.16
libiconv_url ?= ${GNU_MIRROR}/libiconv/libiconv-${libiconv_ver}.tar.gz
gmp_ver ?= 6.1.2
gmp_url ?= ${GNU_MIRROR}/gmp/gmp-${gmp_ver}.tar.xz
mpfr_ver ?= 4.0.2
mpfr_url ?= ${GNU_MIRROR}/mpfr/mpfr-${mpfr_ver}.tar.xz
mpc_ver ?= 1.1.0
mpc_url ?= ${GNU_MIRROR}/mpc/mpc-${mpc_ver}.tar.gz
include mk/toolchain.mk

deb_deps:
	${SUDO} apt install ${deb_deps}

fetch:
	[ -f cache/gcc-${gcc_ver}.tar.xz ] || (cd cache; wget ${gcc_url})
	[ -f cache/gcc-${gcc_ver}.tar.xz.sig ] || (cd cache; wget ${gcc_url}.sig)
	[ -f cache/binutils-${binutils_ver}.tar.xz ] || (cd cache; wget ${binutils_url})
	[ -f cache/binutils-${binutils_ver}.tar.xz.sig ] || (cd cache; wget ${binutils_url}.sig)
	[ -f cache/libiconv-${libiconv_ver}.tar.gz ] || (cd cache; wget ${libiconv_url})
	[ -f cache/libiconv-${libiconv_ver}.tar.gz.sig ] || (cd cache; wget ${libiconv_url}.sig)
	[ -f cache/gmp-${gmp_ver}.tar.xz ] || (cd cache; wget ${gmp_url})
	[ -f cache/gmp-${gmp_ver}.tar.xz.sig ] || (cd cache; wget ${gmp_url}.sig)
	[ -f cache/mpfr-${mpfr_ver}.tar.xz ] || (cd cache; wget ${mpfr_url})
	[ -f cache/mpfr-${mpfr_ver}.tar.xz.sig ] || (cd cache; wget ${mpfr_url}.sig)
	[ -f cache/mpc-${mpc_ver}.tar.gz ] || (cd cache; wget ${mpc_url})
	[ -f cache/mpc-${mpc_ver}.tar.gz.sig ] || (cd cache; wget ${mpc_url}.sig)

automaton: deb_deps fetch

world: automaton libiconv binutils gcc

distclean:
	${RM} -r cache/
	mkdir -p cache/
