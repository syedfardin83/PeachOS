#include "kheap.h"
#include "heap.h"
#include "kernel.h"

struct heap kernel_heap;
struct heap_table kernel_heap_table;

void kheap_init(){
    int total_table_entries = PEACH_OS_HEAP_SIZE_BYTES/PEACH_OS_BLOCK_SIZE_BYTES;
    kernel_heap_table.entries = (HEAP_BLOCK_TABLE_ENTRY*)PEACH_OS_HEAP_TABLE_ADDRESS;
    kernel_heap_table.total = total_table_entries;
    void* heap_end = (void*)PEACH_OS_HEAP_ADDRESS + PEACH_OS_HEAP_SIZE_BYTES;
    
    //  Creating the kernel heap
    int res = heap_create(&kernel_heap,(void*)PEACH_OS_HEAP_ADDRESS,heap_end,&kernel_heap_table);
    if(res<0){
        print("\nError initializing kernel heap!");
    }else{
        print("\nSucessfully initialized kernel heap!");
    }
}

void* kmalloc(size_t size){
    return heap_malloc(&kernel_heap, PEACH_OS_HEAP_SIZE_BYTES);
}