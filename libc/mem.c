#include "mem.h"

void memcpy(uint8_t *source, uint8_t *destination, int size) {
    int i;

    for(i = 0; i < size; i++) {
        *(destination + i) = *(source + i);
    }
}

void memset(uint8_t *destination, uint8_t value, uint32_t size) {
    uint8_t *temp = (uint8_t *) destination;

    for(; size!=0; size--) *temp++ = value;
}

uint32_t free_mem_addr = 0x10000;

uint32_t kmalloc(uint32_t size, int align, uint32_t *physical_address) {
    if(align == 1 && (free_mem_addr & 0xFFFFF000)) {
        free_mem_addr &= 0xFFFFF000;
        free_mem_addr += 0x1000;
    }

    if(physical_address) *physical_address = free_mem_addr;

    uint32_t value = free_mem_addr;
    free_mem_addr += size;
    return value;
}
