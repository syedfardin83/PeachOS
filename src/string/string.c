#include "string.h"

int strnlen(const char* ptr,int max){
    int len=0;
    while(*ptr!=0){
        if(len>=max) return max;
        len++;
        ptr+=1;
    }
    return len;
}

int strlen(const char* ptr)
{
    int i = 0;
    while(*ptr != 0)
    {
        i++;
        ptr += 1;
    }

    return i;
}

int to_numeric_digit(char c){
    return c-48;
}

bool is_digit(char c){
    return (c>=48 && c<=57);
}

char* strcpy(char* dest, const char* src){
    char* res = dest;
    while(*src!='\0'){
        *dest = *src;
        src+=1;
        dest+=1;
    }
    *dest = '\0';

    return res;
}