// Config for target device/peripherals
// Hardcoding addresses determined by SoC,
// eventually replace w/ DTB

#pragma once

#define MEM_BASE    0x40000000u     //physical memory base address
#define UART_BASE   0x09000000u     //uart pl011 base address
#define CLOCK_HZ    0x24000000u
