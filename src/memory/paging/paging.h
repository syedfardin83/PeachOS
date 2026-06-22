#ifndef PAGING_H
#define PAGING_H

#include <stdint.h>
#include <stddef.h>

#define PAGING_IS_PRESENT      0b00000001
#define PAGING_ACCESS_FROM_ALL 0b00000100
#define PAGING_CACHE_DISABLED  0b00010000
#define PAGING_WRITE_THROUGH   0b00000100
#define PAGING_IS_WRITABLE     0b00000010

#define PAGING_TOTAL_ENTRIES_PER_TABLE 1024
#define PAGING_PAGE_SIZE 4096

struct page_directory{
    uint32_t* entries;
};


// asm functions
void paging_enable();
// void paging_load_directory(uint32_t*);

void paging_switch(uint32_t* directory);
#endif