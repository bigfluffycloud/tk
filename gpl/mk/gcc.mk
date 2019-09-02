gcc_conf += --with-bugurl="https://osdev.ninja/bugs/:project=tk/"

ifeq (x${CPU_X86},x1)
gcc_conf += --target=i686-elf
endif

ifeq (x${CPU_X86_64},x1)
gcc_conf += --target=x86_64
endif

gcc_conf += --prefix="${PREFIX}"
#gcc_conf += --with-sysroot=
gcc_conf += --enable-multiarch
gcc_conf += --disable-nls
gcc_conf += --enable-langauges=c,c++

