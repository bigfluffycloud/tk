.globl cons_vga_read_font

cons_vga_read_font:
		/*in: edi=4k buffer
		 *out: buffer filled with font
		 *clear even/odd mode
		 */
		mov			$0x03ce, %dx
		mov			5, %ax
		out			%ax, %dx
		//map VGA memory to 0A0000h
		mov			$0x0406, %ax
		out			%ax, %dx
		//set bitplane 2
		mov			$0x03c4, %dx
		mov			$0x0402, %ax
		out			%ax, %dx
		//clear even/odd mode (the other way, don't ask why)
		mov			$0x0604, %ax
		out			%ax, %dx
		//copy charmap
		mov			$0x0A0000, %esi
		mov			256, %ecx
		//copy 16 bytes to bitmap
nextchar:
		movsd
		movsd
		movsd
		movsd
		//skip another 16 bytes
		add			16, %esi
		loop			nextchar
		//restore VGA state to normal operation
		mov			$0x0302, %ax
		out			%ax, %dx
		mov			$0x0204, %ax
		out			%ax, %dx
		mov			$0x03ce, %dx
		mov			$0x1005, %ax
		out			%ax, %dx
		mov			$0x0E06, %ax
		out			%ax, %dx
