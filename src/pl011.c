// UART Driver (PL011)
#include "bsp_virt.h"
#include "mmio.h"
#include "pl011.h"
#include <stdbool.h>

struct pl011_ctx get_pl011_ctx(
        uintptr_t base,
        uint32_t clock_hz)
{
    return (struct pl011_ctx) {
        .base=          base,
        .clock_hz=      clock_hz,
        .dr_offset=     0x00,
        .fr_offset=     0x18,
        .cr_offset=     0x30,
        .ibrd_offset=   0x24,
        .fbrd_offset=   0x28,
        .lcrh_offset=   0x2C,
        .imsc_offset=   0x38,
        .icr_offset=    0x44,
    };
}

void pl011_init(struct pl011_ctx *ctx)
{
    //disable uart
    mmio_write32(ctx->base, ctx->cr_offset, 0x0);
    //clear pending interrupts
    mmio_write32(ctx->base, ctx->icr_offset, 0x7FF);
    //set baud rate (hard coded assuming 24MHz clock_hz)
    mmio_write32(ctx->base, ctx->ibrd_offset, 13);
    mmio_write32(ctx->base, ctx->fbrd_offset, 2);
    //enable FIFO & 8 bit data transmission
    mmio_write32(ctx->base, ctx->lcrh_offset, (1<<4)|(1<<5)|(1<<6));
    //mask all interrupts
    mmio_write32(ctx->base, ctx->imsc_offset,
            (1<<1)|(1<<4)|(1<<5)|(1<<6)|
            (1<<7)|(1<<8)|(1<<9)|(1<<10));
    //enable uart receive & transfer part
    mmio_write32(ctx->base, ctx->cr_offset, (1<<0)|(1<<8)|(1<<9));
}

void pl011_putc(unsigned char c, struct pl011_ctx *ctx)
{
    while (mmio_read32(ctx->base, ctx->fr_offset) & (1<<5));
    mmio_write32(ctx->base, ctx->dr_offset, c);
}

unsigned char pl011_getc(struct pl011_ctx *ctx)
{
    while (mmio_read32(ctx->base, ctx->fr_offset) & (1<<4));
    return mmio_read32(ctx->base, ctx->dr_offset);
}

void pl011_puts(const char* buf, struct pl011_ctx *ctx)
{
    for (size_t i = 0; buf[i] != '\0'; i++) {
        pl011_putc((unsigned char)buf[i], ctx);
    }
}

void pl011_putb(uint8_t byte, struct pl011_ctx *ctx)
{
    while (mmio_read32(ctx->base, ctx->fr_offset) & (1<<5));
    mmio_write32(ctx->base, ctx->dr_offset, byte);
}

//map nibble to hex char
static inline char hex_digit(uint8_t nib) {
    uint8_t mask = 0x0F;                            //this is redundant, nib is masked in put_hex
    nib &= mask;
    return (nib < 10) ? ('0' + nib) : ('A' + (nib - 10));
}

void pl011_put_hex(const uint64_t data, struct pl011_ctx *ctx)
{
    //prefix
    pl011_putc('0', ctx);
    pl011_putc('x', ctx);
    uint8_t mask = 0x0F;                            //keep only 4 low bits
    for (int shift = 60; shift >= 0; shift -=4 ) {
        uint8_t nib = (data >> shift) & mask;
        pl011_putc(hex_digit(nib), ctx);
    }
}
