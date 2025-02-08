#define TEXT_COLOUR 0x0f
#include <stdbool.h>
#include "games.h"
#include "screen.h"
#include "cursor.h"

void kernel() {
    clear_screen(0x0f);
    char welcome[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    char moo[] = "Moo";
    char tux[] = "BustOS is better than Linux";
    printf(welcome, TEXT_COLOUR);
    cowsay(moo, TEXT_COLOUR);
    tuxsay(tux, TEXT_COLOUR);
    //set_cursor(0, 41);
    while (true) {}
}