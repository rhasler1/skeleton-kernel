

static void uart_putc(char c);
void uart_puts(const char *s);

void kernel_main(void) {
    uart_puts("Hello World, from kernel!");
    while (1) {}
}

// For QEMU's -machine virt, the UART is an ARM PL011 at address 0x09000000
// volatile: prevent compiler optimization & caching 
#define UART0 ((volatile unsigned int *)0x09000000)

static void uart_putc(char c) {
    // Check if UART is ready to transmit by checking
    // Flag Register at UART0 + 0x18
    while (*(UART0 + 0x18/4) & (1<<5)) ;

    // Writes this byte into the UART's Data Register at offset 0x00
    // This enqueues the byte into the UART's transmit FIFO.
    *UART0 = c;
}

void uart_puts(const char *s) {
    while (*s) {
        if (*s == '\n') {
            uart_putc('\r');        // add carriage return for terminal compatibility
        }
        uart_putc(*s++);            // send the character
    }
}
