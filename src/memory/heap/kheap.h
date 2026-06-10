#ifndef KHEAP_H
#define KHEAP_H

#include "config.h"
#include <stddef.h>
#include <stdint.h>

void kheap_init();
void* kmalloc(size_t size);

#endif