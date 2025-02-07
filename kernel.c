#define TEXT_COLOUR 0xf0
#include <stdbool.h>
#include "screen.h"

void kernel() {
    char letter[] = "Bs";
    char s = 's';
    printChar(s, TEXT_COLOUR);
    //printf (letter, TEXT_COLOUR);
    //printChar(letter[0], TEXT_COLOUR);
    //printChar(letter[1], TEXT_COLOUR);
    while (true) {}
}