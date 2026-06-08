#include "kheap.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init(){
    int total_table_entries = PEACH_OS_HEAP_SIZE_BYTES/PEACH_OS_BLOCK_SIZE_BYTES;
    
}