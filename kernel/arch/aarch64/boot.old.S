.section .text
.global _start
_start:

    // Figure out which core we are on using MPIDR_EL1
    mrs     x0, MPIDR_EL1
    and     x0, x0, #0xFF     // Affinity level 0 (core ID)

    cbz     x0, 1f            // if core == 0, jump to label 1 and continue boot

// Secondary cores park here:
0:
    wfe                        // wait for event (low-power idle loop)
    b       0b                 // stay here forever (or until you later wake them)

1:
    //setup stack
    ldr x5, =stack_top
    mov sp, x5

    ldr x1, =boot_addr

    bl kernel_main

.section .bss.stack
    .balign 4096
stack_bottom:
    .skip 4096 * 16                 //64KiB
stack_top:                          //linker.ld

//.data: Initialized Variables::Begin
.section .data
    .balign     8
    .global     boot_adr
    .type       boot_adr, %object
    .size       boot_adr, 8
boot_addr: .quad 0x80000
//Initialized Variables::End
