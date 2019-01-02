#include "keyboard.h"

#include "../cpu/isr.h"
#include "../cpu/ports.h"

#include "../libc/types.h"
#include "../libc/string.h"
#include "../libc/stdin.h"

#include "../drivers/screen.h"

static int prev_scode = 0;
static int times[256];
static bool send = true;

static void keyboard_callback(registers_t reg) {
    uint8_t scancode = inb(0x60);

    bool key_up = false;

    if(scancode >= 0x80) {
        key_up = true;
        scancode -= 0x80;
    }

    if(scancode > SCAN_MAX) return;

    if(key_up == true) {
        keydown[(int) scancode] = false;
    } else {
        keydown[(int) scancode] = true;

        if((int) scancode != prev_scode) {
            times[(int) scancode] = 0;
            prev_scode = (int) scancode;
            send = true;
        } else {
            if(scancode != BACKSPACE) {
                send = false;
                times[(int) scancode] += 1;
            } else {
                send = true;
                times[(int) scancode] = 0;
            }
        }
    }

    if(times[(int) scancode] >= 2) {
        send = true;
        times[(int) scancode] = 0;
    }

    if(send == true) {
        key_handler();
    }
}

void init_keyboard() {
    register_interrupt_handler(IRQ1, keyboard_callback);
}
