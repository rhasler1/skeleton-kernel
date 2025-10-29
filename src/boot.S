.section .text

.global _start
_start:
    //setup stack
    ldr x5, =stack_top
    mov sp, x5

    //save DTB
    ldr x2, =0x40000000         // For baremetal QEMU virt, addr of DTB is not passed through register
    ldr x1, =phandle
    str x2, [x1]

    //Working on getting current Exception Level
    mrs x0, CurrentEL
    lsr x0, x0, #2
    ldr x3, =ex_level
    str x0, [x3]
    
    // Call C function
    bl kernel_main

1:  wfe
    b 1b

// .bss.stack: Stack Initialized to 0 on 4096 byte boundary
.section .bss.stack
    .balign 4096
stack_bottom:
    .skip 4096 * 16                 //64KB Stack
stack_top:                          //Set in linker.ld

//.data: Initialized Variables::Begin
.section .data
    // Device Tree
    .balign     8                   // align on 8 byte boundary
    .global     phandle             // phandle = Device Tree Pointer
    .type       phandle, %object
    .size       phandle, 8          // reserve 8 bytes
phandle: .quad  0                   // init to 0   
    // Test
    .balign     8
    .global     test
    .type       test, %object
    .size       test, 8
test: .quad       0x0F                 // Why "quad" to signify 8 (4"quad"*2"word"?)
    .balign     8
    .global     ex_level
    .type       ex_level, %object
    .size       ex_level, 8
ex_level: .quad 0

//Initialized Variables::End

