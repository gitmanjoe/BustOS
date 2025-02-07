#define TEXT_COLOUR 0x0f
#include <stdbool.h>
#include "games.h"
#include "screen.h"
#include "cursor.h"

void kernel() {
    clear_screen(0x0f);
    char sigma[] = "Welcome To BustOS - 32 Bit Protected Mode\n";
    printf(sigma, TEXT_COLOUR);
    set_cursor(0, 41);
    while (true) {}
}