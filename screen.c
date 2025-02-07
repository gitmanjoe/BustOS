#include "screen.h"
#include <stdbool.h>

char* video_memory = (char*) 0xb8000;

void printChar(char charToPrint, int color)
{
    *video_memory++ = charToPrint;
    *video_memory++ = color;
}

void printf(char strtoPrint[], int color)
{
    for(int i = 0; strtoPrint[i] != 0; i++){
        printChar(strtoPrint[i], color);
    }
    //crlf();
}

void crlf()
{
    printChar(0x0d, 0x00);
    printChar(0x0a, 0x00);
}