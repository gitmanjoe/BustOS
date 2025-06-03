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
#include "hardware.h"
#include "sound.h"

#define OSVER "1.0"

char prompt[] = "BustOS>";

void kernel() {
    set_colour(TEXT_COLOUR);
    clear_screen();

    print_logo();

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

    crlf();
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

    //Convert 1st token to uppercase to remove case sensitivity
    capitalize_string(tokens[0]);

    if (compare_string(tokens[0], "ECHO") ==0) {
        // Combine all tokens after ECHO
        char message[256] = "";
        combine_tokens(tokens, token_count, message);

        crlf();
        printf(message);
    }
    else if (compare_string(tokens[0], "COWSAY") ==0) {
        //char msg[] = "\nCowsay\n";
        //printf(msg);

        // Combine all tokens after COWSAY
        char message[256] = "";
        combine_tokens(tokens, token_count, message);

        crlf();
        cowsay(message);
    }
    else if (compare_string(tokens[0], "TUXSAY") ==0) {
        //char msg[] = "\nTuxsay\n";
        //printf(msg);

        // Combine all tokens after TUXSAY
        char message[256] = "";
        combine_tokens(tokens, token_count, message);

        crlf();
        tuxsay(message);
    }
    else if (compare_string(tokens[0], "HWINFO") == 0) {
        print_hardware_info();
    }
    else if (compare_string(input, "HELP") == 0) {
        char message[] = "\nECHO: prints to the terminal the string used as a parameter"
                         "\nCOWSAY: Makes a cow say the string used as a parameter"
                         "\nTUXSAY: Makes Tux say the string used as a parameter"
                         "\nHWINFO: Give Specs"
                         "\nCLEAR: Clear screen"
                         "\nVERSION: BustOS Version"
                         "\nEXIT: Leave BustOS\n";
        printf(message);
    }
    else if (compare_string(input, "CLEAR") == 0) {
        clear_screen();
    }
    else if (compare_string(input, "VERSION") == 0) {
        printf("\nBustOS Version ");
        printf(OSVER);
        crlf();
    }
    else if (compare_string(input, "EXIT") == 0) {
        char msg[] = "\nExit\n";
        printf(msg);
        asm volatile("hlt"); // halt cpu
    }
    else if (compare_string(input, "") == 0) {
        
    }
    else {
        char msg[] = ": command not found\n";
        crlf();
        printf(input);
        printf(msg);
    }
    //Debug Info
    //char msg[] = "\ncommand: ";
    //printf(msg);
    //printf(input);
    
    crlf();
    printf(prompt);
}

void _start() {
    kernel();
}