#include "games.h"
#include "screen.h"

void cowsay(char strToCow[], int color)
{
    int strLen = 0;
    for(int i = 0; strToCow[i] = 0; i++)
    {
        strLen++;
    }

    char udsc[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        udsc[i] = '_';
    }

    char dash[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        dash[i] = '-';
    }

    printf("  ", color);
    printf(udsc, color);
    printf("\n", color);
    printf("< ", color);
    printf(strToCow, color);
    printf("  ", color);
    printf(dash, color);
    printf("         \\   ^__^ \n", color);
    printf("          \\  (oo)\\_______\n", color);
    printf("             (__)\\       )\\/\\\\", color);
    printf("                 ||----w |\n", color);
    printf("                 ||     ||\n", color);
}