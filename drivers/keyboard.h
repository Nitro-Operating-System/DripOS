#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../libc/types.h"

#define BACKSPACE 0x0E
#define ENTER     0x1C
#define LSHIFT    0x2A
#define RSHIFT    0x36
#define DELETE    0x00

#define SCAN_MAX  57

extern bool keydown[256]

void init_keyboard();

#endif //KEYBOARD_H
