#include "state.h"
#include "ports.h"
#include "../drivers/screen.h"
#include "../drivers/colors.h"

void sys_state_manager() {
    int tmp_state = get_state();

    switch(tmp_state) {
        case 0:
            // Normal
            break;
        case 1:
            // Shutdown
            outb(0xF4, 0x00);
            break;
        case 2:
            // Crash
            kprint_color("Crash!\n", get_color(RED, BLACK));
            kprint_color("The system has encountered a problem. Halting CPU", get_color(WHITE, BLACK));
            outb(0xF4, 0x00);
            break;
        default:
            // Any state that isn't defined above
            break;
    }
}

int get_state() {
    return state;
}
