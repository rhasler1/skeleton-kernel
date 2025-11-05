// Parsing devicetree, this module is dependent on a subset libfdt
#include "libfdt.h"
#include "fdt.h"
#include "pl011.h"

void test_dtb_addr(uint64_t dtb_addr, struct pl011_ctx *ctx) {
    const void *fdt = (const void *)(uintptr_t)dtb_addr;

    // Raw magic probe
    uint32_t raw = *(volatile const uint32_t *)fdt;
    uint32_t magic = __builtin_bswap32(raw); // expect 0xd00dfeed

    pl011_puts("\nMagic number= ", ctx);
    pl011_put_hex((uint64_t)magic, ctx);

    int res = fdt_check_header(fdt);
    if (res != 0) {
        pl011_puts("\nInvalid DTB; Error Code: ", ctx);
        pl011_put_hex((uint64_t)res, ctx);
        pl011_puts("\n", ctx);
        return;
    }

    pl011_puts("\nLooking for /memory node in DTB...\n", ctx);
    int off = fdt_path_offset(fdt, "/memory");
    if (off >= 0) {
        int len;
        const uint64_t *reg = fdt_getprop(fdt, off, "reg", &len);
        pl011_puts("Found /memory node\n", ctx);
    }
}

