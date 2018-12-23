#ifndef MEM_H
#define MEM_H

#include "types.h"

void memcpy(uint8_t *source, uint8_t *destination, int size);
void memset(uint8_t *destination, uint8_t value, uint32_t size);

uint32_t kmalloc(uint32_t size, int align, uint32_t *physical_address);

#endif //MEM_H
