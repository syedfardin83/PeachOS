#include "heap.h"
#include "status.h"
#include <stdbool.h>
#include <stdint.h>
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

static uint32_t heap_align_value_to_upper(uint32_t val){
    if((val%PEACH_OS_BLOCK_SIZE_BYTES)==0){
        return val;
    }
    val=val-(val&PEACH_OS_BLOCK_SIZE_BYTES);
    val+=PEACH_OS_BLOCK_SIZE_BYTES;
    return val;

}

static int heap_get_entry_type(HEAP_BLOCK_TABLE_ENTRY entry){
    return entry & 0x0f;
}

int heap_find_start_block(struct heap* heap, uint32_t total_blocks){
    struct heap_table* table = heap->table;

    int bc=0;
    int bs=-1;

    for(size_t i=0;i<(table->total)*PEACH_OS_BLOCK_SIZE_BYTES;i++){
        if(heap_get_entry_type(table->entries[i])!=HEAP_BLOCK_TABLE_ENTRY_FREE){
            bc = 0;
            bs = -1;
            continue;
        }
        if(bs==-1){
            bs=i;
        }
        bc++;
        if(bc==total_blocks){
            break;
        }
    }
    if(bs==-1){
        return -ENOMEM;
    }
    return bs;
}

void* heap_block_to_addr(struct heap* heap, int start_block){
    return heap->saddr + start_block*PEACH_OS_BLOCK_SIZE_BYTES;
}

void heap_mark_blocks_taken(struct heap* heap, int start_block, int total_blocks){
    HEAP_BLOCK_TABLE_ENTRY entry;
    if(total_blocks==1){
        heap->table->entries[start_block] = HEAP_BLOCK_IS_FIRST | HEAP_BLOCK_TABLE_ENTRY_TAKEN;
        return;
    }
    else{
        for(int i=1;i<=total_blocks;i++){
            entry = HEAP_BLOCK_TABLE_ENTRY_TAKEN;
            if(i<total_blocks) entry |= HEAP_BLOCK_HAS_NEXT;
            heap->table->entries[start_block+i] = entry;
        }
    }
}

void* heap_malloc_blocks(struct heap* heap, uint32_t total_blocks){
    void* addr = 0x00;

    int start_block = heap_find_start_block(heap, total_blocks);
    if(start_block<0){
        goto out;
    }

    addr = heap_block_to_addr(heap,start_block);

    heap_mark_blocks_taken(heap, start_block, total_blocks);

out:
    return addr;
}

void* heap_malloc(struct heap* heap,size_t size){

    size_t aligned_size = heap_align_value_to_upper(size);
    uint32_t total_blocks = aligned_size/PEACH_OS_BLOCK_SIZE_BYTES;

    return heap_malloc_blocks(heap, total_blocks);
}

int heap_free(struct heap* heap, void* ptr){
    int res = 0;



    return res;
}