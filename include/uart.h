#pragma once
#include <stdint.h>
#include <stddef.h>

void uart_init();
void uart_hw_init(uintptr_t base, uint32_t clock_hz);

void uart_puts(const char* buf, uintptr_t base);
void uart_putc(unsigned char c, uintptr_t base);
unsigned char uart_getc(uintptr_t base);

