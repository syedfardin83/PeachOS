#include "paging.h"
#include "memory.h"

struct page_directory* new_4gb(uint8_t flags){
    uint32_t* directory = kzalloc(sizeof(uint32_t)*PAGING_TOTAL_ENTRIES_PER_TABLE);

    //  Creating the 1024 page tables
    for(int i=0;i<PAGING_TOTAL_ENTRIES_PER_TABLE;i++){
        uint32_t* page_table = kzalloc(sizeof(uint32_t)*PAGING_TOTAL_ENTRIES_PER_TABLE);
        // Lineraly map all entries of page table
        for(int j=0;j<PAGING_TOTAL_ENTRIES_PER_TABLE;j++){
            page_table[j] = ((i*PAGING_TOTAL_ENTRIES_PER_TABLE+j)*PAGING_PAGE_SIZE) | flags;
        }
        directory[i] = page_table;
    }

    struct page_directory* new_4gb = kzalloc(sizeof(struct page_directory));
    new_4gb->entries = directory;
    return new_4gb;
}