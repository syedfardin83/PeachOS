#include "heap.h"
#include <stdbool.h>

static bool heap_validate_alignment(void* ptr){
    return ((unsigned int)ptr % PEACH_OS_BLOCK_SIZE_BYTES) == 0;
}

int heap_create(struct heap* heap, void* ptr, void* end, struct heap_table* table){
    int res = 0;


    return res;  
}