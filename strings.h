// strings.h
#pragma once

#define MAX_TOKENS 32  //String lenght for split_string

int string_length(char s[]);
void reverse(char s[]);
void int_to_string(int n, char str[]);
int backspace(char s[]);
void append(char s[], char n);
int compare_string(char s1[], char s2[]);
void split_string(char* str, char delim, char** tokens, int* token_count);
void append_string(char* s1, char* s2);
void capitalize_string(char s[]);