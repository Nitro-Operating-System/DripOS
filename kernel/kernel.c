#include "kernel.h"
#include "../cpu/isr.h"
#include "../cpu/state.h"
#include "../cpu/timer.h"

// Drivers
#include "../drivers/screen.h"

// Lib
#include "../libc/string.h"

int state = 0;

void main() {
    isr_install();
    irq_install();
    init_timer(1);

    clear_screen();
    logoDraw();
    wait(100);
    clear_screen();

    kprint("DripOS v0.0.1");
}