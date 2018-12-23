#include "keyboard.h"

#include "../cpu/isr.h"
#include "../cpu/ports.h"
#include "../libc/string.h"
#include "../drivers/screen.h"

int key_timeout[256];
static char key_buffer[2560];

static void keyboard_callback(registers_t reg) {
    uint8_t scancode = inb(0x60);

    bool key_up = false;

    if(scancode >= 0x80) {
        key_up = true;
        scancode -= 0x80;
    }

    if(scancode > SCAN_MAX) return;
}
