OUTPUT_FORMAT("elf32-i386")
OUTPUT_ARCH(i386)

ENTRY(_entry)

SECTIONS {
   . = 0x00100000;

   __start = .;
   .text ALIGN(4096) : {
      *(.text)
      *(.gnu.linkonce.t*)
   }

   .rodata ALIGN (4096) : {
      *(.rodata)
      *(.gnu.linkonce.r*)
      __ctor_list = .;
      *(.ctors)
      __ctor_end = .;
      __dtor_list = .;
      *(.dtors)
      __dtor_end = .;
   }

   .data ALIGN (4096) : {
      *(.data)
      *(.gnu.linkonce.d*)
   }

   .got : {
      *(.got.plt)
      *(.got)
   }

   .dynamic : {
      *(.dynamic)
   }

   .bss : {
      __bss = .;
      *(COMMON)
      *(.bss)
      *(.gnu.linkonce.b*)
      __ebss = .;
   }

   __end = .;

   /DISCARD/ : {
      *(.comment*)
      *(.eh_frame)
      *(.note*)
   }
}
