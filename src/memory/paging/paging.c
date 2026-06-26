#include "paging.h"
#include "memory.h"
#include "kheap.h"


static uint32_t* current_directory = 0;
void paging_load_directory(uint32_t*);

struct paging_4gb_chunk* paging_new_4gb(uint8_t flags){
    uint32_t* directory = kzalloc(sizeof(uint32_t)*PAGING_TOTAL_ENTRIES_PER_TABLE);

    //  Creating the 1024 page tables
    for(int i=0;i<PAGING_TOTAL_ENTRIES_PER_TABLE;i++){
        uint32_t* page_table = kzalloc(sizeof(uint32_t)*PAGING_TOTAL_ENTRIES_PER_TABLE);
        // Linerally map all entries of page table
        for(int j=0;j<PAGING_TOTAL_ENTRIES_PER_TABLE;j++){
            page_table[j] = ((i*PAGING_TOTAL_ENTRIES_PER_TABLE+j)*PAGING_PAGE_SIZE) | flags;
        }
        directory[i] = (uint32_t)page_table | flags | PAGING_IS_WRITABLE;
    }

    struct paging_4gb_chunk* new_4gb = kzalloc(sizeof(struct paging_4gb_chunk));
    new_4gb->entries = directory;
    return new_4gb;
}

void paging_switch(uint32_t* directory){
    paging_load_directory(directory);
    current_directory=directory;
}