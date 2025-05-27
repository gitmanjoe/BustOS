#define TEXT_COLOUR 0x0a
#include <stdbool.h>
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
    //print_logo();
    char welcome[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    printf(welcome);

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

    //char moo[] = "BustOS";
    //char tux[] = "Linux Sucks";
    //cowsay(moo);
    //tuxsay(tux);

    while (true) {}
}

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