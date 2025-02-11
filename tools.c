#include "tools.h"
#include "screen.h"

#define BLK_WHI 0x0f

void print_logo(int color){char logo1[] = " ____            _    ___  ____ \n";char logo2[] = "| __ ) _   _ ___| |_ / _ \\/ ___|\n";char logo3[] = "|  _ \\| | | / __| __| | | \\___ \\ \n";char logo4[] = "| |_) | |_| \\__ \\ |_| |_| |___) |\n";char logo5[] = "|____/ \\__,_|___/\\__|\\___/|____/ \n";printf(logo1, color);printf(logo2, color);printf(logo3, color);printf(logo4, color);printf(logo5, color);}
void enable_interrupts(){__asm__ volatile("sti");}
int str_to_int(char* str){
    int num = 0;
    for (int i = 0; str[i] != 0; i++) {
        if(str[i] == '0'){
            num = num * 10 + 0;
        }
        if(str[i] == '1'){
            num = num * 10 + 1;
        }
        if(str[i] == '2'){
            num = num * 10 + 2;
        }
        if(str[i] == '3'){
            num = num * 10 + 3;
        }
        if(str[i] == '4'){
            num = num * 10 + 4;
        }
        if(str[i] == '5'){
            num = num * 10 + 5;
        }
        if(str[i] == '6'){
            num = num * 10 + 6;
        }
        if(str[i] == '7'){
            num = num * 10 + 7;
        }
        if(str[i] == '8'){
            num = num * 10 + 8;
        }
        if(str[i] == '9'){
            num = num * 10 + 9;
        }
    }
    return num;
}