#define TEXT_COLOUR 0x0f
#include <stdbool.h>
#include "games.h"
#include "screen.h"

void kernel() {
    clear_screen(0x0f);
    char sigma[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    char moo[] = "I like oiled up men";
    printf(sigma, TEXT_COLOUR);
    cowsay(moo, TEXT_COLOUR);
    while (true) {}
}