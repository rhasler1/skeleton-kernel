.section .text

.global _start
_start:
    ldr x5, =stack_top
    mov sp, x5

    //Working on getting current Exception Level
    //mrs x0, CurrentEL
    //lsr x0, x0, #2
    //ldr x1, =current_el
    //str x0, [x1]
    
    // Call C function
    bl kernel_main

1:  wfe
    b 1b

// Uninitialized globals & statics
// Stack is defined here
.section .bss
    // 2^12 = 4096 byte boundary
    // This means assembler/linker ensures the label
    // starts at an address divisible by 4096.
    .align 12
stack_bottom:
    .skip 4096 * 16     //64KB Stack
stack_top:

.section .data
    .align  4
    .global EL
    .type   EL, %object
    .size   EL, 8
EL: .quad   0x123456789ABCDEF0

