// UART Driver (PL011)
#include "uart.h"
#include "bsp_virt.h"
#include "mmio.h"

/*struct pl011_ctx {
    uintptr_t   pl011_base;
    uint32_t    pl011_clock;
    uint32_t    off_cr;
    uint32_t    off_ibrd;
    uint32_t    off_fbrd;
    uint32_t    off_lcrh;
    uint32_t    off_imsc;
    uint32_t    off_icr;
};

struct pl011_ctx get_pl011_ctx(uintptr_t base, uint32_t clock_hz)
{
    return (pl011_ctx) {
        .pl011_base=    base,
        .pl011_clock=   clock_hz,
        .off_cr=        0x30,
        .off_ibrd=      0x24,
        .off_fbrd=      0x28,
        .off_lcrh=      0x2C,
        .off_imsc=      0x38,
        .off_icr=       0x44,
    };
}*/

void uart_init(struct bsp_uart_cfg *cfg)
{
    //struct bsp_uart_cfg cfg = get_bsp_uart_cfg(void);
    uart_hw_init(cfg->base, cfg->clock_hz);
}

void uart_hw_init(uintptr_t base, uint32_t clock_hz)
{
    uint32_t uart_dr_off =       0x00;
    uint32_t uart_fr_off =       0x18;
    uint32_t uart_cr_off =       0x30;
    uint32_t uart_ibrd_off =     0x24;
    uint32_t uart_fbrd_off =     0x28;
    uint32_t uart_lcrh_off =     0x2C;
    uint32_t uart_imsc_off =     0x38;
    uint32_t uart_icr_off =      0x44;

    //disable uart
    mmio_write32(base, uart_cr_off, 0x0);
    //clear pending interrupts
    mmio_write32(base, uart_icr_off, 0x7FF);
    //set baud rate (hard coded assuming 24MHz clock_hz)
    mmio_write32(base, uart_ibrd_off, 13);
    mmio_write32(base, uart_fbrd_off, 2);
    //enable FIFO & 8 bit data transmission
    mmio_write32(base, uart_lcrh_off, (1<<4)|(1<<5)|(1<<6));
    //mask all interrupts
    mmio_write32(base, uart_imsc_off,
            (1<<1)|(1<<4)|(1<<5)|(1<<6)|
            (1<<7)|(1<<8)|(1<<9)|(1<<10));
    //enable uart receive & transfer part
    mmio_write32(base, uart_cr_off, (1<<0)|(1<<8)|(1<<9));
}

void uart_putc(unsigned char c, uintptr_t base)
{
    uint32_t uart_dr_off = 0x00;
    uint32_t uart_fr_off = 0x18;
    while (mmio_read32(base, uart_fr_off) & (1<<5));
    mmio_write32(base, uart_dr_off, c);
}

unsigned char uart_getc(uintptr_t base)
{
    uint32_t uart_dr_off = 0x00;
    uint32_t uart_fr_off = 0x18;
    while (mmio_read32(base, uart_fr_off) & (1<<4));
    return mmio_read32(base, uart_dr_off);
}

void uart_puts(const char* buf, uintptr_t base)
{
    for (size_t i = 0; buf[i] != '\0'; i++) {
        uart_putc((unsigned char)buf[i], base);
    }
}

