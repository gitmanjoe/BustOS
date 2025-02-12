#define TEXT_COLOUR 0x0a
#include <stdbool.h>
#include "games.h"
#include "screen.h"
#include "cursor.h"
#include "tools.h"

void kernel() 
{
    set_colour(TEXT_COLOUR);
    clear_screen();
    print_logo();
    char welcome[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    char moo[] = "I love BBC";
    char tux[] = "Linux Sucks";
    printf(welcome);
    cowsay(moo);
    tuxsay(tux);
    set_cursor(69, 69);
    while (true) {}
}