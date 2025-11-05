//#include "bsp_virt.h"
#include "pl011.h"
#include "dtb.h"
#include <stdint.h>
#include <stddef.h>

extern uint64_t dtb_addr;
//extern uint64_t test;
extern uint64_t ex_level;

void init_uart(struct pl011_ctx *ctx)
{
    pl011_init(ctx);
    pl011_puts("\n---Testing serial communication over pl011 UART---\n", ctx);
    pl011_puts("Success", ctx);
}

void check_el(struct pl011_ctx *ctx)
{
    pl011_puts("\n---Checking kernel exception level---\nex_level= ", ctx);
    uint64_t el = ex_level;
    pl011_put_hex(el, ctx);
}

void check_dtb(struct pl011_ctx *ctx)
{
    pl011_puts("\n---Checking Devicetree blob---\ndtb_addr= ", ctx);
    uint64_t da = dtb_addr;
    pl011_put_hex(da, ctx);
    test_dtb_addr(da, ctx);
}

void kernel_main(void) {
    // hardcode, DTB is not parsed at this point
    uintptr_t uart_base = 0x9000000;
    uint32_t clock_hz = 24000000;
    // get pl011 struct
    struct pl011_ctx ctx = get_pl011_ctx(uart_base, clock_hz);
    // init pl011
    init_uart(&ctx);
    // check kernel exception level
    check_el(&ctx);
    // check dtb_addr
    check_dtb(&ctx);

    while (1) {}
}
