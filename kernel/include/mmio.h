#pragma once

#include <stdint.h>

#define MMIO_BASE ((uintptr_t)0xFE000000)

uint32_t mmio_read(
        uint32_t reg
        );

void mmio_write(
        uint32_t reg,
        uint32_t data
        );
