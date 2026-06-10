#include "heap.h"
#include "status.h"
#include <stdbool.h>
#include "memory.h"

static int heap_validate_table(void* ptr, void* end, struct heap_table* table){
    int res = 0;
    int total_blocks = (end-ptr)/PEACH_OS_BLOCK_SIZE_BYTES;
    if(!(total_blocks==table->total)){
        res = -EINVARG;
    }
    return res;
}

static bool heap_validate_alignment(void* ptr){
    return ((unsigned int)ptr % PEACH_OS_BLOCK_SIZE_BYTES) == 0;
}

int heap_create(struct heap* heap, void* ptr, void* end, struct heap_table* table){
    int res = 0;

    if(!heap_validate_alignment(ptr) || !heap_validate_alignment(end)){
        res = -EINVARG;
        goto out;
    }

    memset(heap, 0, sizeof(heap));

    heap->saddr=ptr;
    heap->table=table;

    res = heap_validate_table(ptr,end,table);
    if(res<0){
        goto out;
    }

    size_t table_size = PEACH_OS_BLOCK_SIZE_BYTES * table->total;
    memset(table->entries,HEAP_BLOCK_TABLE_ENTRY_FREE,table_size);

out:
    return res;  
}