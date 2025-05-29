// strings.c
// string manipulation functions
#include "strings.h"
#include "types.h"
// return string length
int string_length(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}
// reverse string
void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = string_length(s) - 1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}
// convert int to string
void int_to_string(int n, char str[]) {
    int i = 0;
    int is_negative = 0;

    if (n == 0) {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    if (n < 0) {
        is_negative = 1;
        // Handle INT_MIN safely
        if (n == -2147483648) {
            // Special case for INT_MIN
            // "-2147483648"
            char min_int[] = "-2147483648";
            int j = 0;
            while (min_int[j]) {
                str[j] = min_int[j];
                j++;
            }
            str[j] = '\0';
            return;
        }
        n = -n;
    }

    while (n != 0) {
        str[i++] = (n % 10) + '0';
        n /= 10;
    }

    if (is_negative)
        str[i++] = '-';

    str[i] = '\0';
    reverse(str);
}
// append char to a string
void append(char s[], char n) {
    int len = string_length(s);
    if (len < 255) { // Fix: prevent buffer overflow
        s[len] = n;
        s[len + 1] = '\0';
    }
}
// remove last char in a string
int backspace(char s[]) {
    int len = string_length(s);
    if (len > 0) {
        s[len - 1] = '\0';
        return 1;
    }
    else {
        return 0;
    }
}
// compare two strings
// Returns <0 if s1 < s2, 0 if s1 == s2, >0 if s1>s2
int compare_string(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}