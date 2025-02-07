#define TEXT_COLOUR 0xf0
#include <stdbool.h>
#include <screen.h>

void kernel() {
    char letter = 'B'
    /*char* video_memory = (char*) 0xb8000;
    *video_memory++ = 'X';
    *video_memory++ = TEXT_COLOUR;*/
    printChar (letter, TEXT_COLOUR);
    while (true) {}
}