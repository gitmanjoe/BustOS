#include "games.h"
#include "screen.h"

void cowsay(char strToSay[])
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
    char cow3[] = "             (__)\\       )\\/\\\n";
    char cow4[] = "                 ||----w |\n";
    char cow5[] = "                 ||     ||\n";

    //PRINT THE COW!!!!!
    printf(twoSpaces);
    printf(udsc);
    printf(newLine);
    printf(lessThanSpace);
    printf(strToSay);
    printf(greaterThanSpace);
    printf(newLine);
    printf(twoSpaces);
    printf(dash);
    printf(newLine);
    printf(cow1);
    printf(cow2);
    printf(cow3);
    printf(cow4);
    printf(cow5);
}

void tuxsay(char strToSay[])
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
    char tux9[] = "    \\___)=(___/\n";

    //PRINT TUX!!!!!
    printf(twoSpaces);
    printf(udsc);
    printf(newLine);
    printf(lessThanSpace);
    printf(strToSay);
    printf(greaterThanSpace);
    printf(newLine);
    printf(twoSpaces);
    printf(dash);
    printf(newLine);
    printf(tux1);
    printf(tux2);
    printf(tux3);
    printf(tux4);
    printf(tux5);
    printf(tux6);
    printf(tux7);
    printf(tux8);
    printf(tux9);
}

