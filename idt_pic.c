#include "idt_pic.h"

#define IDT_SIZE 256
#define KERNEL_CODE_SEGMENT 0x08  // Code segment selector from GDT
#define PIC1 0x20                 // Master PIC
#define PIC2 0xA0                 // Slave PIC
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)
#define PIC_EOI 0x20              // End-of-interrupt command
#define KEYBOARD_IRQ 1
#define IRQ_BASE 32               // IRQs start at 32 in the IDT

// IDT Entry structure
struct IDTEntry {
    uint16_t base_low;
    uint16_t sel;
    uint8_t always0;
    uint8_t flags;
    uint16_t base_high;
} __attribute__((packed));

// IDT Pointer structure
struct IDTPointer {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

// Declare the IDT and IDT pointer
static struct IDTEntry idt[IDT_SIZE];
static struct IDTPointer idt_ptr;

// External keyboard ISR (from assembly)
extern void keyboard_isr();
extern void load_idt(struct IDTPointer* idt_ptr);

// Inline functions for I/O operations
static inline void outb(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t value;
    __asm__ volatile ("inb %1, %0" : "=a"(value) : "Nd"(port));
    return value;
}

// Function to set an IDT entry
static void set_idt_entry(int index, uint32_t base, uint16_t sel, uint8_t flags) {
    idt[index].base_low = base & 0xFFFF;
    idt[index].sel = sel;
    idt[index].always0 = 0;
    idt[index].flags = flags;
    idt[index].base_high = (base >> 16) & 0xFFFF;
}

// Remap the PIC (to avoid conflicts with CPU exceptions)
static void remap_pic() {
    outb(PIC1_COMMAND, 0x11); // Start initialization
    outb(PIC2_COMMAND, 0x11);
    outb(PIC1_DATA, IRQ_BASE); // Master PIC vector offset
    outb(PIC2_DATA, IRQ_BASE + 8); // Slave PIC vector offset
    outb(PIC1_DATA, 0x04); // Tell Master PIC about Slave
    outb(PIC2_DATA, 0x02); // Tell Slave PIC its cascade identity
    outb(PIC1_DATA, 0x01); // Set 8086 mode
    outb(PIC2_DATA, 0x01);
    outb(PIC1_DATA, 0x0); // Enable all IRQs
    outb(PIC2_DATA, 0x0);
}

// Enable interrupts (assembly)
static void enable_interrupts() {
    __asm__ volatile ("sti");
}

// Setup IDT and PIC
void setup_idt_and_pic() {
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;

    // Set keyboard interrupt (IRQ1 -> IDT[IRQ_BASE + 1])
    set_idt_entry(IRQ_BASE + KEYBOARD_IRQ, (uint32_t)keyboard_isr, KERNEL_CODE_SEGMENT, 0x8E);

    remap_pic(); // Setup PIC
    load_idt(&idt_ptr); // Load the IDT
    enable_interrupts(); // Enable CPU interrupts
}
