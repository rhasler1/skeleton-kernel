#include "device_config.h"

.section .text
.global _start
_start:
    //setup stack
    ldr x5, =stack_top
    mov sp, x5

    //QEMU virt stores dtb starting at 0x40000000
    ldr x2, =MEM_BASE
    ldr x1, =dtb_addr
    str x2, [x1]

    //working on getting current Exception Level
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ldr x3, =ex_level
    str x0, [x3]
    
    bl kernel_main

1:  wfe
    b 1b

// .bss.stack: Stack Initialized to 0 on 4096 byte boundary
.section .bss.stack
    .balign 4096
stack_bottom:
    .skip 4096 * 16                 //64KiB
stack_top:                          //linker.ld

//.data: Initialized Variables::Begin
.section .data
    .balign     8                   //8 byte boundary
    .global     dtb_addr
    .type       dtb_addr, %object
    .size       dtb_addr, 8         //reserve 8 bytes
dtb_addr: .quad  0                  //init to 0   
    .balign     8
    .global     ex_level
    .type       ex_level, %object
    .size       ex_level, 8
ex_level: .quad 0
//Initialized Variables::End
