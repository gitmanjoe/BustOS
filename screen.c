#include "screen.h"
#include <stdbool.h>

void printChar (char charToPrint, int color);

void printChar (char charToPrint, int color)
{
    char* video_memory = (char*) 0xb8000;
    *video_memory++ = charToPrint;
    *video_memory++ = color;
}

void printString (string strtoPrint, int color)
{
    while
}