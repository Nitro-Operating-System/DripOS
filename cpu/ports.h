#ifndef PORTS_H
#define PORTS_H

#include "../libc/types.h"

// Sends a 8-bit value to a I/O location
void outb(uint16_t port, uint8_t value);
// Fetches a 8-bit value from a I/O location
uint8_t inb(uint16_t port);

// Sends a 16-bit value to a I/O location
void outw(uint16_t port, uint16_t value);
// Fetches a 16-bit value from a I/O location
uint16_t inw(uint16_t port);

// Sends a 32-bit value to a I/O location
void outl(uint16_t port, uint32_t value);
// Fetches a 32-bit value from a I/O location
uint32_t inl(uint16_t port);

#endif //PORTS_H
