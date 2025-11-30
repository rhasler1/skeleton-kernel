#pragma once
#include "gpio.h"
#include <stdint.h>

//pl011 UART
#define UART0_BASE      (GPIO_BASE + 0x1000)

//offset for each register
#define UART0_DR              (UART0_BASE + 0x00)             //data register
#define UART0_RSRECR          (UART0_BASE + 0x04)             //receive status/error clear register
#define UART0_FR              (UART0_BASE + 0x18)             //flag register
#define UART0_ILPR            (UART0_BASE + 0x20)             //infrared mode low-power counter register
#define UART0_IBRD            (UART0_BASE + 0x24)             //integer baud rate divisor
#define UART0_FBRD            (UART0_BASE + 0x28)             //fractional baud rate divisor
#define UART0_LCRH            (UART0_BASE + 0x2C)             //line control register, high byte
#define UART0_CR              (UART0_BASE + 0x30)             //control register
#define UART0_IFLS            (UART0_BASE + 0x34)             //interrupt FIFO level select
#define UART0_IMSC            (UART0_BASE + 0x38)             //interrupt mask set/clear register
#define UART0_RIS             (UART0_BASE + 0x3C)             //raw interrupt status
#define UART0_MIS             (UART0_BASE + 0x40)             //masked interrupt status
#define UART0_ICR             (UART0_BASE + 0x44)             //interrupt clear register
#define UART0_DMACR           (UART0_BASE + 0x48)             //DMA control register
#define UART0_ITCR            (UART0_BASE + 0x80)             //integration test control register
#define UART0_ITIP            (UART0_BASE + 0x84)             //integration test input register
#define UART0_ITOP            (UART0_BASE + 0x88)             //integration test output register
#define UART0_TDR             (UART0_BASE + 0x8C)             //test data register

void            init_uart0          ();
void            uart0_putc          (unsigned char c);
unsigned char   uart0_getc          ();
void            uart0_puts          (const char* buf);
void            uart0_put_hex       (const uint64_t data);
