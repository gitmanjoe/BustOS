#define TEXT_COLOUR 0x0f
#include <stdbool.h>
#include "games.h"
#include "screen.h"

void kernel() {
    clear_screen(0x0f);
    char sigma[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    printf(sigma, TEXT_COLOUR);
    cowsay("moo shit", TEXT_COLOUR);
    while (true) {}
}