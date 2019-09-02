deb_deps += build-essential bison flex libgmp3-dev libmpc-dev libmpfr-dev texinfo libisl-dev
# libcloog-isl-dev

###################
stage ?= 1

PREFIX ?= /opt/tk/stage-${stage}/

binutils_conf += --prefix="${PREFIX}"
binutils_conf += --disable-nls --disable-werror
binutils_conf += --enable-gold=no --enable-ld=yes
binutils_conf += --disable-libquadmath
#binutils_conf += 
#binutils_conf += 

# GCC - GNU C Compiler collection
gcc_conf += --prefix="${PREFIX}"
gcc_conf += --disable-nls
gcc_conf += --enable-languages=c,c++
gcc_conf += --with-multilib-list=m32
#gcc_conf += --enable-targets=all
gcc_conf += --enable-default-pie --enable-default-ssp
gcc_conf += --disable-libada --disable-libquadmath-support
# change to posix later
gcc_conf += --enable-threads=single --enable-tls=no
gcc_conf += --disable-bootstrap
#gcc_conf += --with-sysroot=${PREFIX}/
#gcc_conf += --with-build-sysroot=${PREFIX}/
gcc_conf += --without-headers

binutils-unpack:
	mkdir -p build/src/
	cd build/src; tar xvf ../../cache/binutils-${binutils_ver}.tar.xz

build/src/binutils-${binutils_ver}/configure.ac:
	${MAKE} binutils-unpack

binutils: build/src/binutils-${binutils_ver}/configure.ac
	mkdir -p build/build-binutils
	cd build/build-binutils; ../src/binutils-${binutils_ver}/configure ${binutils_conf}
	${MAKE} -j4 -C build/build-binutils && ${SUDO} ${MAKE} -C build/build-binutils install

gcc-unpack:
	mkdir -p build/src/
	cd build/src; tar xvf ../../cache/gcc-${gcc_ver}.tar.xz

build/src/gcc-${gcc_ver}/configure.ac:
	${MAKE} gcc-unpack

gcc: build/src/gcc-${gcc_ver}/configure.ac
	mkdir -p build/build-gcc
	cd build/build-gcc; ../src/gcc-${gcc_ver}/configure ${gcc_conf}
	${MAKE} -j4 -C build/build-gcc && ${SUDO} ${MAKE} -C build/build-gcc install
