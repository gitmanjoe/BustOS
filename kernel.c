// kernel3.c
// install the ISRs, loading IDT.
// enable external interrupts by setting the interrupt flag using sti.
// call the init_keyboard function that registers the keyboard interrupt handler.
#include "screen.h"
#include "strings.h"
#include "isr.h"
#include "keyboard.h"
void kernel () {
//clear_screen();
//char message[] = "OsX Kernel running in 32 bit protected mode";
//print_string(message);
clear_screen();
char msg1[] = "Installing interrupt service routines (ISRs).\n";
print_string(msg1);
isr_install();
char msg2[] = "Enabling external interrupts.\n";
print_string(msg2);
asm volatile("sti");
30
copyright © 2022 www.onlineprogramminglessons.com For student use only
char msg3[] = "Initializing keyboard (IRQ 1).\n";
print_string(msg3);
init_keyboard();
 char prompt[] = "\nOSX> ";
print_string(prompt);
}
// receive commands to execute
void execute_command(char* input) {
 // exit command
 char exitmsg[] = "EXIT";
if (compare_string(input, exitmsg) == 0) {
char msg[] = "Exit\n";
print_string(msg);
asm volatile("hlt"); // halt cpu
}
char msg[] = "\ncommand: ";
print_string(msg);
print_string(input);
char prompt[] = "\nOSX> ";
print_string(prompt);
}