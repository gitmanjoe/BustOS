#include "games.h"
#include "screen.h"

void cowsay(char strToCow[], int color)
{
    //Getting the length of the string
    int strLen = 0;
    for(int i = 0; strToCow[i] = 0; i++)
    {
        strLen++;
    }

    //Getting the line of _'s on top
    char udsc[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        udsc[i] = '_';
    }

    //Getting the line of -'s underneath
    char dash[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        dash[i] = '-';
    }

    //Variable initalization
    char twoSpaces[] = "  ";
    char newLine[] = "\n"
    char lessThanSpace[] = "< ";
    char greaterThanSpace[] = "> ";
    char cow1[] = "         \\   ^__^ \n";
    char cow2[] = "          \\  (oo)\\_______\n";
    char cow3[] = "             (__)\\       )\\/\\\\";
    char cow4[] = "                 ||----w |\n";
    char cow5[] = "                 ||     ||\n";

    //PRINT THE COW!!!!!
    printf(twoSpaces, color);
    printf(udsc, color);
    printf(newLine, color);
    printf(lessThanSpace, color);
    printf(strToCow, color);
    printf(greaterThanSpace, color);
    printf(newLine, color);
    printf(twoSpaces, color);
    printf(dash, color);
    printf(newLine, color);
    printf(cow1, color);
    printf(cow2, color);
    printf(cow3, color);
    printf(cow4, color);
    printf(cow5, color);
}