.section .text



.global _start


// 0. set up 64kb stack


// 1. branch to kernel main


_start:


    ldr x0, =stack_top


    mov sp, x0





    // Call C function


    bl kernel_main





// Safety-net in case kernel main returns.


// This should not happen.


1:  wfe


    b 1b





.section .bss


    // 2^12 = 4096 byte boundary


    // This means assembler/linker ensures the label


    // starts at an address divisible by 4096.


    .align 12





stack_bottom:


    // 64KB stack


    .skip 4096 * 16





// stack_top is determined in the linker script, see src/linker.ld


stack_top:


