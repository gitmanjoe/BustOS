static void printChar (char charToPrint int colo)
{
    char* video_memory = (char*) 0xb8000;
    *video_memory++ = charToPrint;
    *video_memory++ = TEXT_COLOUR;
}