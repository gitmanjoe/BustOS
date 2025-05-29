#include "screen.h"
#include "cursor.h"
#include <stdbool.h>

#define VIDEO_ADDRESS 0xb8000
#define NEW_LINE_HEX 0xA0

int offset[] = {0,0};
int colour = 0x0f;
void crlf();
void scroll_screen();

void printChar(char charToPrint)
{
    if (charToPrint == '\n') {
        crlf();
        return;
    }
    if (offset[0] > 79) {
        offset[0] = 0;
        offset[1]++;
    }
    if (offset[1] > 24) {
        scroll_screen();
        offset[1] = 24;
    }
    char* vmp = (char*) VIDEO_ADDRESS + offset[0] * 2 + offset[1] * 160;
    *vmp++ = charToPrint;
    *vmp = colour;
    ++offset[0];
    set_cursor(offset[1], offset[0]);
}

void printf(char strtoPrint[])
{
    for(int i = 0; strtoPrint[i] != 0; i++){
        printChar(strtoPrint[i]);
    }
}

void print_backspace() {
    if (offset[0] > 0) {
        offset[0]--;
    } else if (offset[1] > 0) {
        offset[1]--;
        offset[0] = 79;
    }
    char* vmp = (char*) VIDEO_ADDRESS + offset[0] * 2 + offset[1] * 160;
    *vmp++ = ' ';
    *vmp = colour;
    set_cursor(offset[1], offset[0]);
}

void crlf()
{
    offset[0] = 0;
    offset[1] = ++offset[1];
}

void clear_screen(){
    char* vmp = (char*) VIDEO_ADDRESS;
    for(int i = 0; i < 80 * 25; i++){
        *vmp++ = ' ';
        *vmp++ = colour;
    }
    offset[0] = 0;
    offset[1] = 0;
    set_cursor(0, 0);
}

void set_offset(int x, int y){
    offset[0] = x;
    offset[1] = y;
}

void set_colour(int color){
    colour = color;
}

void scroll_screen() {
    char* vmp = (char*) VIDEO_ADDRESS;
    // Copy each line up
    for (int row = 1; row < 25; row++) {
        for (int col = 0; col < 80; col++) {
            int from = row * 160 + col * 2;
            int to = (row - 1) * 160 + col * 2;
            vmp[to] = vmp[from];
            vmp[to + 1] = vmp[from + 1];
        }
    }
    // Clear the last line
    for (int col = 0; col < 80; col++) {
        int pos = 24 * 160 + col * 2;
        vmp[pos] = ' ';
        vmp[pos + 1] = colour;
    }
}