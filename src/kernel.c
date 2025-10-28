#include "bsp_virt.h"
#include "pl011.h"
#include <stdint.h>
#include <stddef.h>

extern uint64_t phandle;
extern uint64_t test;

void kernel_main(void) {
    // BSP Uart Config (SoC)
    struct bsp_uart_cfg cfg =   get_bsp_uart_cfg();
    // pl011 Config/Context
    struct pl011_ctx ctx =      get_pl011_ctx(cfg.base, cfg.clock_hz);     
    pl011_init(&ctx);
    pl011_puts("Hello World!\n", &ctx);

    uint64_t fdt = phandle;
    uint64_t t = test;
    pl011_put_hex(t, &ctx);

    while (1) {}
}
