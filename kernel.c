#define TEXT_COLOUR 0xf0
#include <stdbool.h>
#include "screen.h"

void kernel() {
    clear_screen(TEXT_COLOUR);
    char sigma[] = "Hello, World";
    char sigma1[] = "die, sigma";
    //printf(sigma, TEXT_COLOUR);
    //printf(sigma1, TEXT_COLOUR);
    while (true) {}
}