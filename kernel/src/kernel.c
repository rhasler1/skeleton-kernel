#include "uart0.h"
#include <stdint.h>

void kernel_main(uint64_t dtb_ptr32, uint64_t x1, uint64_t x2, uint64_t x3)
{
    init_uart0();
    uart0_puts("\nHello World!\n");

    while (1) {
        uart0_putc(uart0_getc());
    }
}
