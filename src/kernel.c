// Specifications are for the QEMU virt board.
// Change values to match target board.
// This module is largely based on https://wiki.osdev.org/Raspberry_Pi_Bare_Bones
// Baud rate is hard coded: calculations are provided.

#include "uart.h"
#include "mmio.h"

void kernel_main(void) {
    uart_init();
    uart_puts("Hello World! From Skeleton.");
    while (1) {}
}
