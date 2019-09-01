tk
==
tk is a tiny kernel. It's designed to provide a very
minimal base for Library OS / Exokernel experimentation on virtual machines.


This is based on what I've been been able to recover of the original
popcorn/tk kernel source. A few files had to be remvoed as their license
forbids their distribution.

To use this mess, you need some things:
	gcc
	binutils
	grub (grub-legacy)
	mtools
	qemu (bochs coming soon)
	nasm
	*patience*

if you get an error about cannot find /usr/lib/grub/i386-pc/...:
	Edit .config to point to wherever your grub stages are:
		Arch Linux: /usr/lib/grub/i386-pc

-OR-
	Use syslinux ;)

Getting started:

	Check out
		git clone git://github.com/bigfluffycloud/tk/

	Build
		make floppy

	Test
		make qemu

	Fix stuff ;)

	Submit


Since we usually run on virtualization, most filesystems are either in-memory or network.