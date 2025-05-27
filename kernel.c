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
//char message[] = "BustOS Kernel running in 32 bit protected mode";
//printf(message);
clear_screen();
char msg1[] = "Installing interrupt service routines (ISRs).\n";
printf(msg1);
isr_install();
char msg2[] = "Enabling external interrupts.\n";
printf(msg2);
asm volatile("sti");
char msg3[] = "Initializing keyboard (IRQ 1).\n";
printf(msg3);
init_keyboard();
char prompt[] = "\nBustOS> ";
printf(prompt);
}
// receive commands to execute
void execute_command(char* input) {
 // exit command
 char exitmsg[] = "EXIT";
if (compare_string(input, exitmsg) == 0) {
char msg[] = "Exit\n";
printf(msg);
asm volatile("hlt"); // halt cpu
}
char msg[] = "\ncommand: ";
printf(msg);
printf(input);
char prompt[] = "\nBustOS> ";
printf(prompt);
}