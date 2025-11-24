#pragma once
#include <stdint.h>

uint32_t mmio_read32(
        uintptr_t base,
        uint32_t offset
        );

void mmio_write32(
        uintptr_t base,
        uint32_t offset,
        uint32_t data
        );
