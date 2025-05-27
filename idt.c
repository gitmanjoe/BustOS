// idt.c
// interrupt description table setup IDT
#include "idt.h"
#include "strings.h"
idt_gate_t idt[IDT_ENTRIES]; // idt table
idt_register_t idt_reg; // idt register
// register interrupt handler
void set_idt_gate(int n, unsigned int handler) {
    idt[n].low_offset = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].always0 = 0;
    idt[n].flags = 0x8E;
    idt[n].high_offset = high_16(handler);
}
// load idt register
void load_idt() {
    idt_reg.base = (unsigned int)&idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_gate_t) - 1;
    // load &idt_reg using lidt instruction
    asm volatile("lidt (%0)" : : "r" (&idt_reg));
}