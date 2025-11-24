#include "device_config.h"

/* Link boot.S and kernel.c */
ENTRY(_start)

SECTIONS {
  . = 0x40100000;
  
  .text : {
    *(.text*)
  }

  .rodata : {
    *(.rodata*)
  }

  .data : {
    *(.data*)
  }

  .bss : {
    *(.bss*)
    *(COMMON)
  }
}
