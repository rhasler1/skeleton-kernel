// Specifications are for the QEMU virt board.
// Change values to match target board.
// This module is largely based on https://wiki.osdev.org/Raspberry_Pi_Bare_Bones
// Baud rate is hard coded: calculations are provided.

#include "uart.h"
#include "mmio.h"

void kernel_main(void) {
    uart_init();
    uart_puts("Starting Skeleton Kernel...\n");

    // Read counter frequency
    uint64_t counter_freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(counter_freq));        // cntfrq_el0 is a system register w/ counter frequency

    // Read current counter
    uint64_t counter_curr;
    asm volatile("mrs %0, cntvct_el0" : "=r"(counter_curr));

    // Set compare value = now + 1s
    uint64_t counter_next = counter_curr + counter_freq;
    asm volatile("msr cntv_cval_el0, %0" :: "r"(counter_next));     // write value x0 into virtual timer compare register, this scheduels the next interrupt

    // Enable virtual timer
    asm volatile("msr cntv_ctl_el0, %0" :: "r"(1));

    // Unmask IRQ at CPU level
    asm volatile("msr daifclr, #2"); // Clear I (IRQ mask)

    uart_puts("Timer armed. Waiting...\n");

    while (1) {
        asm volatile("wfe");        // wfe=wait for event
    }
}
