#define TEXT_COLOUR 0xf0
#include <stdbool.h>
#include "screen.h"

void kernel() {
    //clear_screen(TEXT_COLOUR);
    char sigma[] = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    printf(sigma, TEXT_COLOUR);
    //printf(sigma1, TEXT_COLOUR);
    while (true) {}
}