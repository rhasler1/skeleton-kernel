// Parsing devicetree
// This module is dependent on libfdt
//
//
#include "libfdt.h"
#include "fdt.h"
#include "pl011.h"

//extern uint64_t phandle;

void test_fdt_phandle(uint64_t phandle, struct pl011_ctx *ctx) {
    pl011_puts("\nINSIDE OF TEST_FDT_PHANDLE\n", ctx);
    pl011_put_hex(phandle, ctx);
    uint32_t new_phandle = 0x40000000u;
    const void *fdt = (const void *)(uintptr_t)0x40100000u;

    // Optional raw magic probe
    uint32_t raw = *(volatile const uint32_t *)fdt;
    uint32_t magic = __builtin_bswap32(raw); // expect 0xd00dfeed

    pl011_put_hex((uint64_t)magic, ctx);

    int res = fdt_check_header(fdt);
    if (res != 0) {
        pl011_puts("Invalid DTB; Error Code: ", ctx);
        pl011_put_hex((uint64_t)res, ctx);
        return;
    }

    int off = fdt_path_offset(fdt, "/memory");
    if (off >= 0) {
        int len;
        const uint64_t *reg = fdt_getprop(fdt, off, "reg", &len);
        pl011_puts("Found /memory node\n", ctx);
    }
}

