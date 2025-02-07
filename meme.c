#define WHITETEXTBLACKBG 0x0f
#include "cowsay.h"
#include "screen.h"

void cowsay(char strToCow[])
{
    strLen = 0;
    for(int i = 0; strToCow[i] = 0; i++)
    {
        strLen++;
    }

    char udsc[]
    for(int i = strLen - 1; i >= 0; i--)
    {
        udsc[i] = '_';
    }

    char dash[]
    for(int i = strLen - 1; i >= 0; i--)
    {
        dash[i] = '_';
    }

    printf("  ", WHITETEXTBLACKBG);
    printf(udsc, WHITETEXTBLACKBG);
    printf("\n"), WHITETEXTBLACKBG;
    printf("< ", WHITETEXTBLACKBG);
    printf(strToCow, WHITETEXTBLACKBG);
    printf("  ", WHITETEXTBLACKBG);
    printf(dash, WHITETEXTBLACKBG);
    printf("         \\   ^__^ \n", WHITETEXTBLACKBG);
    printf("          \\  (oo)\\_______\n", WHITETEXTBLACKBG);
    printf("             (__)\\       )\\/\\\\", WHITETEXTBLACKBG);
    printf("                 ||----w |\n", WHITETEXTBLACKBG);
    printf("                 ||     ||\n", WHITETEXTBLACKBG);
}