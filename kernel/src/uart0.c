#include "uart0.h"
#include "mmio.h"
#include "gpio.h"

#include <stdint.h>
#include <stddef.h>

// Loop <delay> times in a way that the compiler won't optimize away
static inline void delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : "=r"(count): [count]"0"(count) : "cc");
}

void init_uart0()
{
    mmio_write(UART0_CR, 0x00000000);                               //disable uart
    mmio_write(GPPUD, 0x00000000);                                  //disable pull up/down for all GPIO pins
    delay(150);
    mmio_write(GPPUDCLK0, (1 << 14) | (1 << 15));
    delay(150);
    mmio_write(GPPUDCLK0, 0x00000000);                              // write 0 to GPPUDCLK0 to make it take effect
    mmio_write(UART0_ICR, 0x7FF);                                   //clear pending interrupts
    mmio_write(UART0_IBRD, 26);                                     //set baud rate
    mmio_write(UART0_FBRD, 3);                                      //set baud rate
    mmio_write(UART0_LCRH, (1 << 4) | (1 << 5) | (1<<6));           //enable FIFO and 8 bit data transmission
    mmio_write(UART0_IMSC, (1 << 1) | (1 << 4) | (1<<5) |
            (1 << 6) | (1 << 7) | (1 << 8) | (1 << 9) | (1<<10));   //mask all interrupts
    mmio_write(UART0_CR, (1 << 0) | (1 << 8) | (1<<9));             //enable uart0, receieve and transfer part of UART
}

void uart0_putc(unsigned char c)
{
    while (mmio_read(UART0_FR) & (1 << 5)) { }
    mmio_write(UART0_DR, c);
}

unsigned char uart0_getc()
{
    while (mmio_read(UART0_FR) & (1 << 4)) { }
    return mmio_read(UART0_DR);
}

void uart0_puts(const char* buf)
{
    for (size_t i = 0; buf[i] != '\0'; i++) {
        uart0_putc((unsigned char)buf[i]);
    }
}

//map nibble to hex char
static inline char hex_digit(uint8_t nib) {
    uint8_t mask = 0x0F;                            //this is redundant, nib is masked in put_hex
    nib &= mask;
    return (nib < 10) ? ('0' + nib) : ('A' + (nib - 10));
}

void uart0_put_hex(const uint64_t data)
{
    uart0_putc('0');
    uart0_putc('x');
    uint8_t mask = 0x0F;                            //keep only 4 low bits
    for (int shift = 60; shift >= 0; shift -=4 ) {
        uint8_t nib = (data >> shift) & mask;
        uart0_putc(hex_digit(nib));
    }
}
