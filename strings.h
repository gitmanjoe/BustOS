// strings.h
#pragma once
// string manipulation functions
#define low_16(address) (unsigned short)((address) & 0xFFFF)
#define high_16(address) (unsigned short)(((address) >> 16) & 0xFFFF)
int string_length(char s[]);
void reverse(char s[]);
void int_to_string(int n, char str[]);
int backspace(char s[]);
void append(char s[], char n);
int compare_string(char s1[], char s2[]);