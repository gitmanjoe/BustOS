#include "types.h"

void print_logo();
void enable_interrupts();
int str_to_int(char* str);

void memory_copy(char *source, char *dest, int nbytes);
void memory_set(u8 *dest, u8 val, u32 len);
void int_to_ascii(int n, char str[]);