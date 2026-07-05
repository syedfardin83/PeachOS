#ifndef MEMORY_H
#define MEMORY_H

#include <stddef.h>

void* memset(void* ptr, int c, size_t size);
int memcmp(void* p1, void* p2, int count);

#endif