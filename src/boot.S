.section .text

.global _start
_start:
    //setup stack
    ldr x5, =stack_top
    mov sp, x5

    //save DTB
    // DTB is passed in at 0x40100000, see make run
    ldr x2, =0x40100000         // For baremetal QEMU virt, addr of DTB is not passed through register
    ldr x1, =dtb_addr
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
    .global     dtb_addr            // phandle = Device Tree Pointer
    .type       dtb_addr, %object
    .size       dtb_addr, 8         // reserve 8 bytes
dtb_addr: .quad  0                   // init to 0   
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

