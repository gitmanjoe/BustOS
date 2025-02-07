#include <screen.h>

void printChar (char charToPrint int color)
{
    char* video_memory = (char*) 0xb8000;
    *video_memory++ = charToPrint;
    *video_memory++ = color;
}