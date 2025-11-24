#pragma once

#define PAGE_SIZE   4096u
#define ELF_START   0x40100000u
#define ELF_
struct ram_ctx {
    uint64_t    base_addr;
    uint64_t    size;
};
