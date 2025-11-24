#pragma once

#include "mem.h"

int             dtb_check_header    (uint64_t dtb_addr);
struct ram_ctx  get_ram_ctx         (uint64_t dtb_addr);
