#include "tools.h"
#include "screen.h"

#define BLK_WHI 0x0f

void print_logo(){char logo1[] = " ____            _    ___  ____ \n";char logo2[] = "| __ ) _   _ ___| |_ / _ \\/ ___|\n";char logo3[] = "|  _ \\| | | / __| __| | | \\___ \\ \n";char logo4[] = "| |_) | |_| \\__ \\ |_| |_| |___) |\n";char logo5[] = "|____/ \\__,_|___/\\__|\\___/|____/ \n";printf(logo1, BLK_WHI);printf(logo2, BLK_WHI);printf(logo3, BLK_WHI);printf(logo4, BLK_WHI);printf(logo5, BLK_WHI);}
    