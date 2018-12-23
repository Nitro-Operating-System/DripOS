#include "idt.h"

void set_idt_gate(int gate, uint32_t handler) {
    idt[gate].low_offset = (uint16_t)(handler & 0xFFFF);
    idt[gate].sel = Kernel_CS;
    idt[gate].always0 = 0;
    idt[gate].flags = 0x8E;
    idt[gate].high_offset = (uint16_t)((handler >> 16) & 0xFFFF);
}

void set_idt() {
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;

    __asm__ __volatile__ ("lidtl (%0)" : : "r" (&idt_reg));
}