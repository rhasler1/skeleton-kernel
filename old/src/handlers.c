#include <stdint.h>
#include "uart.h"

void sync_handler(void)
{
    uart_puts("[SYNC]\n");
    while (1) { asm volatile("wfe"); }
}
