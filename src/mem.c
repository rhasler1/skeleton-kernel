//beginnings of managing memory and page table
//initial ideas:
//for kernel space use identity mapping
//for OS/User space use User defined VA->PA mapping
//work on paper before starting to code
//need to get RAM physical base address and size
//

//structure of physical pages

struct physical_pages {
    uint64_t                page_size;
    uint64_t                num_pages;
    uint64_t                num_in_use;
    struct physical_page    *pages;
};

struct physical_page {
    size_t      id;
    uint8_t     in_use;         //flag 1=used, 0=avail
    uint64_t    base_addr;      //physical based addr of this page
    uint64_t    *process;       //pointer to base address of process using this physical page
};

struct physical_page init_physical_page(size_t id, uint64_t base_addr, uint64_t page_size)
{
    return (struct physical_page) {
        id=id;
        base_addr=base_addr;
        in_use=0;
        process=void;
    }
}

void init_physical_pages(uint64_t base_addr, uint64_t end_addr, uint64_t page_size)
{
    uint64_t mem_cap = end_addr - base_addr;
    uint64_t num_pages = mem_cap / page_size;
    size_t i;
    for (i = 0; i < num_pages; i++) {
        uint64_t i_base_addr = base_addr + (base_addr * i);
        struct physical_page p = init_physical_page(i, i_base_addr, page_size);
        //?
    }
}

