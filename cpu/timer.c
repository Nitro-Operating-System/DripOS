#include "timer.h"
#include "isr.h"
#include "ports.h"
#include "state.h"

uint32_t current_tick = 0;
uint32_t previous_tick = 0;

static void timer_callback(registers_t registers) {
    sys_state_manager();

    current_tick++;
}

void config_timer(uint32_t time) {
    uint32_t divisor = 1193180 / time;
    uint8_t low = (uint8_t) (divisor & 0xFF);
    uint8_t high = (uint8_t) ((divisor >> 8) & 0xFF);

    outb(0x43, 0x36);
    outb(0x40, low);
    outb(0x40, high);
}

void init_timer(uint32_t frequency) {
    register_interrupt_handler(IRQ0, timer_callback);
    config_timer(frequency);
}

void wait(uint32_t ticks) {
    previous_tick = current_tick;

    while(current_tick - previous_tick < ticks);
}
