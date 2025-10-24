// Board Support Package impl for QEMU Virt
#include "bsp_virt.h"

/* UART */
struct bsp_uart_cfg get_bsp_uart_cfg(void)
{
    return (struct bsp_uart_cfg){
        .base=0x09000000,
        .clock_hz=24000000,
        .irq=33,
    };
}
