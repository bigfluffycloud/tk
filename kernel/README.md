tk
==
tk is a tiny kernel. It's designed to provide a very
minimal base for Library OS / Exokernel experimentation on virtual machines.

Every attempt is being made to make the code readable and correct.

Right now, this isn't very useful. Feel free to help fill in the missing
pieces. We used to be able to run tasks from a packaged initromfs, which
we used to display our demos ;)

This is based on what I've been been able to recover of the original
popcorn/tk kernel source. A few files had to be removed as their license
forbids their distribution. These files have been replaced with versions
from FreeBSD and NetBSD where possible

To use this mess, you need some things:
	gcc
	binutils
	grub (grub-legacy)
	mtools
	qemu or maybe bochs
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
