#pragma once
#include <stdint.h>
#include <stddef.h>

struct pl011_ctx {
    uintptr_t   base;
    uint32_t    clock_hz;
    uint32_t    dr_offset;
    uint32_t    fr_offset;
    uint32_t    cr_offset;
    uint32_t    ibrd_offset;
    uint32_t    fbrd_offset;
    uint32_t    lcrh_offset;
    uint32_t    imsc_offset;
    uint32_t    icr_offset;
};

//return            name            args
struct pl011_ctx    get_pl011_ctx   (uintptr_t base, uint32_t clock_hz);
void                pl011_init      (struct pl011_ctx *ctx);
void                pl011_putc      (unsigned char c, struct pl011_ctx *ctx);
unsigned char       pl011_getc      (struct pl011_ctx *ctx);
void                pl011_puts      (const char *buf, struct pl011_ctx *ctx);
void                pl011_putb      (uint8_t byte, struct pl011_ctx *ctx);
void                pl011_put_hex   (uint64_t data, struct pl011_ctx *ctx);

