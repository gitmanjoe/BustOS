#define TEXT_COLOUR 0x0a
#include <stdbool.h>
#include "games.h"
#include "screen.h"
#include "cursor.h"
#include "tools.h"

void kernel() 
{
    clear_screen(TEXT_COLOUR);
    print_logo(TEXT_COLOUR);
    char welcome[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    char moo[] = "I love BBC";
    char tux[] = "BustOS is better than Linux";
    printf(welcome, TEXT_COLOUR);
    cowsay(moo, TEXT_COLOUR);
    //set_cursor(0, 41);
    while (true) {}
}