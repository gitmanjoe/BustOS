// timer.c
// count timer ticks
#include "timer.h"
#include "ports.h"
#include "isr.h"
#include "screen.h"
unsigned int tick = 0;
// increment timer tick
static void timer_callback(registers_t* regs) {
tick++;
}
//char tickMsg[] = "Tick: ";
//print_string(tickMsg);
// initialize timer
void init_timer(unsigned int freq) {
	// register timer interrupt to IRQ0 service routine
	register_interrupt_handler(IRQ0, timer_callback);

	// set up the desired interval using PIT hardware clock at 1193180 Hz
	unsigned int divisor = 1193180 / freq;
	unsigned char low = (unsigned char)(divisor & 0xFF);
	unsigned char high = (unsigned char)((divisor >> 8) & 0xFF);
	// program PIT
	port_byte_out(0x43, 0x36); // Command port
	port_byte_out(0x40, low);
	port_byte_out(0x40, high);
}