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

void combine_tokens(char* tokens[], int token_count, char* message) {
    for (int i = 1; i < token_count; i++) {
        append_string(message, tokens[i]);
        if (i < token_count - 1) {
            append_string(message, " "); // Add space between words
        }
    }
}

void execute_command(char* input) {
    char* tokens[MAX_TOKENS];  // Make sure MAX_TOKENS is defined in strings.h
    int token_count = 0;

    split_string(input, ' ', tokens, &token_count);

    char cowsaymsg[] = "COWSAY";
    if (compare_string(tokens[0], cowsaymsg) ==0) {
        //char msg[] = "\nCowsay\n";
        //printf(msg);

        // Combine all tokens after COWSAY
        char message[256] = "";
        combine_tokens(tokens, token_count, message);

        crlf();
        cowsay(message);
    }
    char tuxsaymsg[] = "TUXSAY";
    if (compare_string(tokens[0], tuxsaymsg) ==0) {
        //char msg[] = "\nTuxsay\n";
        //printf(msg);

        // Combine all tokens after TUXSAY
        char message[256] = "";
        combine_tokens(tokens, token_count, message);

        crlf();
        tuxsay(message);
    }
    char exitmsg[] = "HELP";
    if (compare_string(input, exitmsg) == 0) {
        //char msg[] = "\nHelp\n";
        //printf(msg);
        char message[] = "\nCOWSAY: Makes a cow say the string used as a parameter"
                         "\nTUXSAY: Makes Tux say the string used as a parameter"
                         "\nCLEAR: Clear screen"
                         "\nEXIT: Leave BustOS\n";
        printf(message);
    }
    char clearmsg[] = "CLEAR";
    if (compare_string(input, clearmsg) == 0) {
        clear_screen();
    }
    char helpmsg[] = "EXIT";
    if (compare_string(input, helpmsg) == 0) {
        char msg[] = "\nExit\n";
        printf(msg);
        asm volatile("hlt"); // halt cpu
    }
    //Debug Info
    //char msg[] = "\ncommand: ";
    //printf(msg);
    //printf(input);

    char prompt[] = "\nBustOS> ";
    printf(prompt);
}

void _start() {
    kernel();
}