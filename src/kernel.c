// Specifications are for the QEMU virt board.
// Change values to match target board.
// This module is largely based on https://wiki.osdev.org/Raspberry_Pi_Bare_Bones
// Baud rate is hard coded: calculations are provided.

#include <stddef.h>
#include <stdint.h>

// 24MHz
#define UART_CLOCK 24000000
// For QEMU's -machine virt, the UART is an ARM PL011 at address 0x09000000
#define UART0_BASE      ( ( volatile unsigned int * ) 0x09000000 )

#define UART0_DR        ( UART0_BASE + 0x00 )
#define UART0_FR        ( UART0_BASE + 0x18 )
#define UART0_IBRD      ( UART0_BASE + 0x24 )
#define UART0_FBRD      ( UART0_BASE + 0x28 )
#define UART0_LCRH      ( UART0_BASE + 0x2C )
#define UART0_CR        ( UART0_BASE + 0x30 )
#define UART0_IMSC      ( UART0_BASE + 0x38 )
#define UART0_ICR       ( UART0_BASE + 0x44 )

static inline void mmio_write(uint32_t reg, uint32_t data)
{
    *(volatile uint32_t*)reg = data;
}

static inline void mmio_read(uint32_t reg)
{
    return *(volatile uint32_t*)reg;
}

void uart_init(void)
{
    // disable UART
    mmio_write(UART0_CR, 0x0);
    // clear interrupts
    mmio_write(UART0_ICR, 0x7FF);
    // set baud rate to 115200 (assuming 24MHz UARTCLK IN QEMU)
    // some math: DIVIDER =       24000000 / (16 * 115200) = 13.021 = ~13
    mmio_write(UART0_IBRD, 13);     // integer
    // some math: FRACTION =    (0.021 * 64) + 0.5 = 1.844 = ~2
    mmio_write(UART0_FBRD, 2);      // fractional
    // enable FIFO & 8 bit data transmission (1 stop bit, no parity)
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1 << 6));
    // mask all interrupts
    mmio_write(UART0_IMSC,
            (1 << 1) | (1 << 4) | (1 << 5) | (1 << 6) |
            (1 << 7) | (1 << 8) | (1 << 9) | (1 << 10));
    // enable UART0, receive & transfer part of UART
    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1 << 9));
}

void uart_putc(unsigned char c)
{
    // wait for UART to become read to transmit
    while ( mmio_read(UART0_FR) & (1 << 5) ) ;
    mmio_write(UART0_DR, c);
}

unsigned char uart_getc()
{
    // wait for UART to have received something
    while ( mmio_read(UART0_FR) & (1 << 4) ) ;
    return mmio_read(UART0_DR);
}

void uart_puts(const char* str)
{
    for (size_t i = 0; str[i] != '\0'; i++) {
        uart_putc( (unsigned char)str[i] );
    }
}

void kernel_main(void) {
    uart_init();
    uart_puts("Hello World! From Skeleton.");
    while (1) {}
}
