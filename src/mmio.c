// MMIO Read/Write Module
#include "mmio.h"

uint32_t mmio_read32(uintptr_t base, uint32_t offset)
{ 
	return *(volatile uint32_t*)(base + offset);
}

void mmio_write32(uintptr_t base, uint32_t offset, uint32_t data)
{
	*(volatile uint32_t*)(base + offset) = data;
}
