#include "screen.h"
#include "cursor.h"
#include <stdbool.h>

#define VIDEO_ADDRESS 0xb8000
#define NEW_LINE_HEX 0xA0

int offset[] = {0,0};
void crlf();

void printChar(char charToPrint, int color)
{
    char* vmp = (char*) VIDEO_ADDRESS;
    vmp = vmp + offset[0] * 2 + offset[1] * NEW_LINE_HEX;
    *vmp++ = charToPrint;
    *vmp++ = color;
}

void printf(char strtoPrint[], int color)
{
    char* vmp = (char*) VIDEO_ADDRESS;
    vmp = vmp + offset[0] * 2 + offset[1] * NEW_LINE_HEX;
    for(int i = 0; strtoPrint[i] != 0; i++){
        char* vmp = (char*) VIDEO_ADDRESS;
        vmp = vmp + offset[0] * 2 + offset[1] * NEW_LINE_HEX;
        if(strtoPrint[i] == '\n'){
            crlf();
        }
        else{
            *vmp++ = strtoPrint[i];
            *vmp = color;
            ++offset[0];
            //offset must be flipped for cursor coords
            set_cursor(offset[1], offset[0]);
        }
        if(offset[0] > 79){
            offset[0] = 0;
            offset[1]++;
        }
    }
}

void crlf()
{
    offset[0] = 0;
    offset[1] = ++offset[1];
}

void clear_screen(int color){
    char* vmp = (char*) VIDEO_ADDRESS;
    for(int i = 0; i <= 80 * 25 * 2; i++){
        *vmp++ = ' ';
        *vmp++ = color;
    }
}

void set_offset(int x, int y){
    offset[0] = x;
    offset[1] = y;
}