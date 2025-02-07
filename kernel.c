# define TEXT_COLOUR 0x0f

void kernel() {
    char* video_memory = (char*) 0xb8000;
    *video_memory++ = 'X';
    *video_memory++ = TEXT_COLOUR;
}