// mem.c
// memory functions
#include "mem.h"
// copy memory from sourse to destination
void memory_copy(unsigned char*source, unsigned char*destination, int
bytes) {
 for (int i = 0; i < bytes; i++) {
 *(destination + i) = *(source + i);
 }
}
// set memory destination of lenth len with a value 
void memory_set(unsigned char *destination, unsigned char value, 
unsigned int len) {
 unsigned char *temp = (unsigned char*)destination;
 for (; len != 0; len--) *temp++ = value;
}