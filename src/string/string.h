#ifndef STRING_H
#define STRING_H

#include <stdbool.h>


int strnlen(const char* ptr,int max);
int strlen(const char* ptr);
int to_numeric_digit(char c);
bool is_digit(char c);

#endif