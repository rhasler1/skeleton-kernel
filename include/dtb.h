#pragma once
#include "pl011.h"

struct physical_memory {
    uint64_t base_addr;
    uint64_t size;
};

int check_dtb_addr(uint64_t dtb_addr, struct pl011_ctx *ctx);
struct physical_memory get_physical_memory_node(uint64_t dtb_addr, struct pl011_ctx *ctx);
