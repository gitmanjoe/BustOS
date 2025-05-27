// interrupt description table setup IDT
//Segment selectors 
#define KERNEL_CS 0x08
// number of IDT entries
#define IDT_ENTRIES 256
// IDT Gate structure
// How every interrupt gate (handler) is defined
#pragma pack(1) // mingw fix for __attribute__((packed)) 
typedef struct {
 unsigned short low_offset; // Lower 16 bits of handler function address 
 unsigned short sel; // Kernel segment selector 
 unsigned char always0;
 // First byte
 // Bit 7: "Interrupt is present"
 // Bits 6-5: Privilege level of caller (0=kernel..3=user)
 // Bit 4: Set to 0 for interrupt gates
 // Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" 
 unsigned char flags;
 unsigned short high_offset; // Higher 16 bits of handler function address
} __attribute__((packed)) idt_gate_t;
// A pointer to the array of interrupt handlers.
// Assembly instruction 'lidt' will read it
#pragma pack(1) // mingw fix for __attribute__((packed))
typedef struct {
 unsigned short limit;
 unsigned int base;
} __attribute__((packed)) idt_register_t;
// register an interrupt handlet
void set_idt_gate(int n, unsigned int handler);
// our IDT as an array of 256 gates
void load_idt();