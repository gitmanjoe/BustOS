#define TEXT_COLOUR 0x0a
#include <stdbool.h>
#include "ports.h"
#include "games.h"
#include "screen.h"
#include "cursor.h"
#include "tools.h"
#include "strings.h"
#include "isr.h"
#include "keyboard.h"
#include "types.h"

void kernel() 
{
    set_colour(TEXT_COLOUR);
    clear_screen();

    char welcome[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    printf(welcome);

    char isr_msg[] = "Installing interrupt service routines (ISRs).\n";
    printf(isr_msg);
    isr_install();

    char kb_msg[] = "Initializing keyboard (IRQ 1).\n";
    printf(kb_msg);
    init_keyboard();

    char enable_msg[] = "Enabling external interrupts.\n";
    printf(enable_msg);
    asm volatile("sti");

    char prompt[] = "\nBustOS>";
    printf(prompt);

    //char tux[] = "Linux Sucks";
    //tuxsay(tux);
}

void execute_command(char* input) {
    // exit command
    char exitmsg[] = "EXIT";
    if (compare_string(input, exitmsg) == 0) {
        char msg[] = "\nExit\n";
        printf(msg);
        asm volatile("hlt"); // halt cpu
    }
    char clearmsg[] = "CLEAR";
    if (compare_string(input, clearmsg) == 0) {
        char msg[] = "\nExit\n";
        clear_screen();
    }
    //Debug Info
    char msg[] = "\ncommand: ";
    printf(msg);
    printf(input);
    char prompt[] = "\nBustOS> ";
    printf(prompt);
}

void _start() {
    kernel();
}