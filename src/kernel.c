//#include "bsp_virt.h"
#include "device_config.h"
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

    int res;
    res = check_dtb_addr(da, ctx);

    if (res != 0) {
        pl011_puts("\n Cannot find Device Tree Blob; FDT error code= ", ctx);
        pl011_put_hex((uint64_t)res, ctx);
    }
    pl011_puts("\nFound Device Tree Blob", ctx);
}

void kernel_main(void) {
    uintptr_t uart_base = UART_BASE;
    uint32_t clock_hz = CLOCK_HZ;
    
    struct pl011_ctx ctx = get_pl011_ctx(uart_base, clock_hz);
    init_uart(&ctx);
    
    check_el(&ctx);
    
    check_dtb(&ctx);
    
    struct physical_memory ram = get_physical_memory_node(dtb_addr, &ctx);
    pl011_put_hex(ram.base_addr, &ctx);

    while (1) {}
}
