#include "screen.h"
#include "cursor.h"
#include <stdbool.h>

#define VIDEO_ADDRESS 0xb8000
#define NEW_LINE_HEX 0xA0

int offset[] = {0,0};
int colour = 0x0f;
void crlf();

void printChar(char charToPrint)
{
    char* vmp = (char*) VIDEO_ADDRESS;
    vmp = vmp + offset[0] * 2 + offset[1] * NEW_LINE_HEX;
    
    if(charToPrint == '\n'){
        crlf();
    }
    else{
        *vmp++ = charToPrint;
        *vmp = colour;
        ++offset[0];
        //offset must be flipped for cursor coords
        set_cursor(offset[1], offset[0]);
    }
    if(offset[0] > 79){
        offset[0] = 0;
        offset[1]++;
    }
}

void printf(char strtoPrint[])
{
    for(int i = 0; strtoPrint[i] != 0; i++){
        printChar(strtoPrint[i]);
    }
}

void print_backspace() {
 printf(' ');
}

void crlf()
{
    offset[0] = 0;
    offset[1] = ++offset[1];
}

void clear_screen(){
    char* vmp = (char*) VIDEO_ADDRESS;
    for(int i = 0; i <= 80 * 25 * 2; i++){
        *vmp++ = ' ';
        *vmp++ = colour;
    }
}

void set_offset(int x, int y){
    offset[0] = x;
    offset[1] = y;
}

void set_colour(int color){
    colour = color;
}