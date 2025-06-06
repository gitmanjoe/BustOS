#include "tools.h"
#include "screen.h"
#include "types.h"

#define BLK_WHI 0x0f

void print_logo(){char logo1[] = " ____            _    ___  ____ \n";char logo2[] = "| __ ) _   _ ___| |_ / _ \\/ ___|\n";char logo3[] = "|  _ \\| | | / __| __| | | \\___ \\ \n";char logo4[] = "| |_) | |_| \\__ \\ |_| |_| |___) |\n";char logo5[] = "|____/ \\__,_|___/\\__|\\___/|____/ \n";printf(logo1);printf(logo2);printf(logo3);printf(logo4);printf(logo5);}
void print_b_logo() {
    char b_logo[] =
    "          _____          \n"
    "         /\\    \\         \n"
    "        /::\\    \\        \n"
    "       /::::\\    \\       \n"
    "      /::::::\\    \\      \n"
    "     /:::/\\:::\\    \\     \n"
    "    /:::/__\\:::\\    \\    \n" //text starts
    "   /::::\\   \\:::\\    \\   \n"
    "  /::::::\\   \\:::\\    \\  \n"
    " /:::/\\:::\\   \\:::\\ ___\\ \n"
    "/:::/__\\:::\\   \\:::|    |\n"
    "\\:::\\   \\:::\\  /:::|____|\n" //29 chars long
    " \\:::\\   \\:::\\/:::/    / \n"
    "  \\:::\\   \\::::::/    /  \n" //text ends
    "   \\:::\\   \\::::/    /   \n"
    "    \\:::\\  /:::/    /    \n"
    "     \\:::\\/:::/    /     \n"
    "      \\::::::/    /      \n"
    "       \\::::/    /       \n"
    "        \\::/____/        \n"
    "         ~~              \n";
    printf(b_logo);
}
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

void memory_copy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(u8 *dest, u8 val, u32 len) {
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}

/**
 * K&R implementation
 */
void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    /* TODO: implement "reverse" */
}

void sleep_ms(unsigned int ms) {
    volatile unsigned int count;
    while (ms--) {
        // This loop is hardware and compiler dependent.
        // Adjust the count value for your CPU speed.
        for (count = 0; count < 10000; count++) {
            __asm__ volatile("nop");
        }
    }
}