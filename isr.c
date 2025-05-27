// isr.c
// interrupt service routines
#include "isr.h"
#include "idt.h"
#include "screen.h"
#include "ports.h"
#include "strings.h"
// table of ibterupt handlers
isr_t interrupt_handlers[256];
// install isrs individually
// isr's names must match with interrupts.asm
void isr_install() {
    // Install the ISRs 0-32 individually
    // isr's names must match with interrupts.asm
    set_idt_gate(0, (unsigned int) isr0);
    set_idt_gate(1, (unsigned int) isr1);
    set_idt_gate(2, (unsigned int) isr2);
    set_idt_gate(3, (unsigned int) isr3);
    set_idt_gate(4, (unsigned int) isr4);
    set_idt_gate(5, (unsigned int) isr5);
    set_idt_gate(6, (unsigned int) isr6);
    set_idt_gate(7, (unsigned int) isr7);
    set_idt_gate(8, (unsigned int) isr8);
    set_idt_gate(9, (unsigned int) isr9);
    set_idt_gate(10, (unsigned int) isr10);
    set_idt_gate(11, (unsigned int) isr11);
    set_idt_gate(12, (unsigned int) isr12);
    set_idt_gate(13, (unsigned int) isr13);
    set_idt_gate(14, (unsigned int) isr14);
    set_idt_gate(15, (unsigned int) isr15);
    set_idt_gate(16, (unsigned int) isr16);
    set_idt_gate(17, (unsigned int) isr17);
    set_idt_gate(18, (unsigned int) isr18);
    set_idt_gate(19, (unsigned int) isr19);
    set_idt_gate(20, (unsigned int) isr20);
    set_idt_gate(21, (unsigned int) isr21);
    set_idt_gate(22, (unsigned int) isr22);
    set_idt_gate(23, (unsigned int) isr23);
    set_idt_gate(24, (unsigned int) isr24);
    set_idt_gate(25, (unsigned int) isr25);
    set_idt_gate(26, (unsigned int) isr26);
    set_idt_gate(27, (unsigned int) isr27);
    set_idt_gate(28, (unsigned int) isr28);
    set_idt_gate(29, (unsigned int) isr29);
    set_idt_gate(30, (unsigned int) isr30);
    set_idt_gate(31, (unsigned int) isr31);
    // Remap the PIC
    // ICW1
    port_byte_out(0x20, 0x11);
    port_byte_out(0xA0, 0x11);

    // ICW2
    port_byte_out(0x21, 0x20);
    port_byte_out(0xA1, 0x28);

    // ICW3
    port_byte_out(0x21, 0x04);
    port_byte_out(0xA1, 0x02);
    // ICW4
    port_byte_out(0x21, 0x01);
    port_byte_out(0xA1, 0x01);
    // OCW1
    port_byte_out(0x21, 0x0);
    port_byte_out(0xA1, 0x0);
    // Install the IRQs ISRs 32-47 individually
    // irq's names must match with interrupts.asm
    set_idt_gate(32, (unsigned int)irq0);
    set_idt_gate(33, (unsigned int)irq1);
    set_idt_gate(34, (unsigned int)irq2);
    set_idt_gate(35, (unsigned int)irq3);
    set_idt_gate(36, (unsigned int)irq4);
    set_idt_gate(37, (unsigned int)irq5);
    set_idt_gate(38, (unsigned int)irq6);
    set_idt_gate(39, (unsigned int)irq7);
    set_idt_gate(40, (unsigned int)irq8);
    set_idt_gate(41, (unsigned int)irq9);
    set_idt_gate(42, (unsigned int)irq10);
    set_idt_gate(43, (unsigned int)irq11);
    set_idt_gate(44, (unsigned int)irq12);
    set_idt_gate(45, (unsigned int)irq13);
    set_idt_gate(46, (unsigned int)irq14);
    set_idt_gate(47, (unsigned int)irq15);
    load_idt(); // Load with ASM
}
// handle isr request
void isr_handler(registers_t* r) {
    // isr exception messages
    char msg0[] = "Division By Zero";
    char msg1[] = "Debug";
    char msg2[] = "Non Maskable Interrupt";
    char msg3[] = "Breakpoint";
    char msg4[] = "Into Detected Overflow";
    char msg5[] = "Out of Bounds";
    char msg6[] = "Invalid Opcode";
    char msg7[] = "No Coprocessor";
    char msg8[] = "Double Fault";
    char msg9[] = "Coprocessor Segment Overrun";
    char msg10[] = "Bad TSS";
    char msg11[] = "Segment Not Present";
    char msg12[] = "Stack Fault";
    char msg13[] = "General Protection Fault";
    char msg14[] = "Page Fault";
    char msg15[] = "Unknown Interrupt";
    char msg16[] = "Coprocessor Fault";
    char msg17[] = "Alignment Check";
    char msg18[] = "Machine Check";
    char msg19[] = "Reserved";
    char msg20[] = "Reserved";
    char msg21[] = "Reserved";
    char msg22[] = "Reserved";
    char msg23[] = "Reserved";
    char msg24[] = "Reserved";
    char msg25[] = "Reserved";
    char msg26[] = "Reserved";
    char msg27[] = "Reserved";
    char msg28[] = "Reserved";
    char msg29[] = "Reserved";
    char msg30[] = "Reserved";
    char msg31[] = "Reserved";

    // array of message pointers
    char* messages[] = { msg0, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8, msg9, 
    msg10, msg11,msg12, msg13, msg14, msg15, msg16, msg17 ,msg18, msg19, msg20, msg21, 
    msg22, msg23, msg24, msg25, msg26, msg27, msg28, msg29, msg30, msg31};
    // report isr interrupt
    char msg[] = "received ISR interrupt: ";
    printf(msg);
    char s[32];
    // print interript number
    int_to_string(r->int_no, s);
    printf(s);
    print_nl();

    // print interrupt message
    printf(messages[r->int_no]);
    print_nl();
}
// register isr handler
void register_interrupt_handler(unsigned char n, isr_t handler) {
    interrupt_handlers[n] = handler;
}
// irq handler
void irq_handler(registers_t *r) {
    //char msg[] = "received IRQ interrupt: ";
    //printf(msg);

    // Handle the interrupt
    if (interrupt_handlers[r->int_no] !=0 && r->int_no > 32) {
    //char text[20];
    //int_to_string(r->int_no, text);
    //printf(text);
    isr_t handler = interrupt_handlers[r->int_no];
    handler(r);
    }
    // EOI
    // tell PIC we are finished
    if (r->int_no >= 40) {
    port_byte_out(0xA0, 0x20); /* follower */
    }
    port_byte_out(0x20, 0x20); /* leader */
}