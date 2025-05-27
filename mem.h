// mem.h
#pragma once
// memory copy and set value functions
void memory_copy(unsigned char* source, unsigned char* destination, 
int bytes);
void memory_set(unsigned char* destination, unsigned char value, 
unsigned int len);