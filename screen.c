#include "screen.h"
#include <stdbool.h>

#define VIDEO_ADDRESS 0xb8000
#define NEW_LINE_HEX 0xA0

int offset[] = {0,0};

void printChar(char charToPrint, int color, char* vmp)
{
    //*vmp++ = charToPrint;
    //*vmp++ = color;
}

void printf(char strtoPrint[], int color)
{
    char* vmp = (char*) VIDEO_ADDRESS;
    vmp += NEW_LINE_HEX;
    for(int i = 0; strtoPrint[i] != 0; i++){
        *vmp++ = strtoPrint[i];
        *vmp++ = color;
    }
    //crlf();
}

void crlf()
{
    offset[0] = 0;
    offset[1] = offset[1] + 0xA0;
}

void clear_screen(int color){
    char* vmp = (char*) VIDEO_ADDRESS;
    vmp += NEW_LINE_HEX;
    for(int i = 0; i <= 80 * 25 * 2; i++){
        *vmp++ = ' ';
        *vmp++ = color;
    }
}