#include "bsp_virt.h"
#include "pl011.h"
#include "dtb.h"
#include <stdint.h>
#include <stddef.h>
//
extern uint64_t phandle;
//extern uint64_t test;
extern uint64_t ex_level;

void kernel_main(void) {
    // BSP UART Config (SoC)
    struct bsp_uart_cfg cfg = get_bsp_uart_cfg();
    // pl011
    struct pl011_ctx ctx = get_pl011_ctx(cfg.base, cfg.clock_hz);     
    pl011_init(&ctx);
    pl011_puts("\n---pl011 UART Initialized---\n", &ctx);
    pl011_puts("\nHello from Kernel Main\n", &ctx);
    // kernel exception level
    pl011_puts("\n---Kernel Exception Level---\n", &ctx);
    uint64_t el = ex_level;
    pl011_put_hex(el, &ctx);
    // parsing device tree
    pl011_puts("\n---DTB Address---\n", &ctx);
    uint64_t dtb_addr = phandle;
    pl011_put_hex(dtb_addr, &ctx);
    pl011_puts("\n", &ctx);
    // testing dtb and libfdt
    pl011_puts("\n---Testing DTB module---\n", &ctx);
    test_fdt_phandle(dtb_addr, &ctx);

    while (1) {}
}
