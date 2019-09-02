OUTPUT_FORMAT("elf64-x86-64")
/*OUTPUT_ARCH(x86-64)*/

ENTRY(_entry)

SECTIONS {
   . = 1M;

   __start = .;
   .text ALIGN(4K) : {
      *(.multiboot)
      *(.text)
      *(.gnu.linkonce.t*)
   }

   .rodata ALIGN (4K) : {
      *(.rodata)
      *(.gnu.linkonce.r*)

      /* Start of C++ Support */
      __ctor_list = .;
      *(.ctors)
      __ctor_end = .;
      __dtor_list = .;
      *(.dtors)
      __dtor_end = .;
      /* End C++ support */
   }

   .data ALIGN (4K) : {
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

   .bss ALIGN(4K) : {
      __bss = .;
      *(COMMON)
      *(.stack)
      *(stack)
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
