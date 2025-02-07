#define TEXT_COLOUR 0xf0
#include <stdbool.h>
#include "screen.h"

void kernel() {
    char letter = 'B';
    printChar (letter, TEXT_COLOUR);
    while (true) {}
}