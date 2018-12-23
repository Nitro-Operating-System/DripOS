#ifndef TIMER_H
#define TIMER_H

#include "../libc/types.h"

void init_timer(uint32_t frequency);
void wait(uint32_t ticks);

uint32_t current_tick;

#endif //TIMER_H
