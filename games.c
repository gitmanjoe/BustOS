#include "games.h"
#include "screen.h"

void cowsay(char strToSay[], int color)
{
    //Get the length of the string
    int strLen = 0;
    for(int i = 0; strToSay[i] != 0; i++)
    {
        strLen++;
    }

    //Get the line of _'s on top
    char udsc[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        udsc[i] = '_';
    }

    //Get the line of -'s underneath
    char dash[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        dash[i] = '-';
    }

    //Variable initalization
    char twoSpaces[] = "  ";
    char newLine[] = "\n";
    char lessThanSpace[] = "< ";
    char greaterThanSpace[] = " >";
    char cow1[] = "         \\   ^__^ \n";
    char cow2[] = "          \\  (oo)\\_______\n";
    char cow3[] = "             (__)\\       )\\/\\\\\n";
    char cow4[] = "                 ||----w |\n";
    char cow5[] = "                 ||     ||\n";

    //PRINT THE COW!!!!!
    printf(twoSpaces, color);
    printf(udsc, color);
    printf(newLine, color);
    printf(lessThanSpace, color);
    printf(strToSay, color);
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

void tuxsay(char strToSay[], int color)
{
    //Get the length of the string
    int strLen = 0;
    for(int i = 0; strToSay[i] != 0; i++)
    {
        strLen++;
    }

    //Get the line of _'s on top
    char udsc[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        udsc[i] = '_';
    }

    //Get the line of -'s underneath
    char dash[32];
    for(int i = strLen - 1; i >= 0; i--)
    {
        dash[i] = '-';
    }

    //Variable initalization
    char twoSpaces[] = "  ";
    char newLine[] = "\n";
    char lessThanSpace[] = "< ";
    char greaterThanSpace[] = " >";
    char tux1[] = "   \\\n";
    char tux2[] = "    \\\n";
    char tux3[] = "        .--.\n";
    char tux4[] = "       |o_o |\n";
    char tux5[] = "       |:_/ |\n";
    char tux6[] = "      //   \\ \\\n";
    char tux7[] = "     (|     | )\n";
    char tux8[] = "    /'\\_   _/`\\\n";
    char tux9[] = "    \\___)|(___/\n";

    //PRINT TUX!!!!!
    printf(twoSpaces, color);
    printf(udsc, color);
    printf(newLine, color);
    printf(lessThanSpace, color);
    printf(strToSay, color);
    printf(greaterThanSpace, color);
    printf(newLine, color);
    printf(twoSpaces, color);
    printf(dash, color);
    printf(newLine, color);
    printf(tux1, color);
    printf(tux2, color);
    printf(tux3, color);
    printf(tux4, color);
    printf(tux5, color);
    printf(tux6, color);
    printf(tux7, color);
    printf(tux8, color);
    printf(tux9, color);
}

