#pragma once
#include <stdint.h>

struct bsp_uart_cfg {
    uintptr_t   base;       // UART MMIO BASE
    uint32_t    clock_hz;   // UART REF CLOCK
    uint32_t    irq;        // INTERRUPT NUM
};

struct bsp_uart_cfg get_bsp_uart_cfg(void);
