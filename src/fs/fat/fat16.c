#include "fat16.h"
#include "string.h"
#include "kheap.h"

int fat16_resolve(struct disk* disk);
void* fat16_open(struct disk* disk, struct path_part* path, FILE_MODE mode);

struct filesystem* fat16_fs;
// struct filesystem fat16_fs = {
//     .resolve = fat16_resolve,
//     .open = fat16_open
// };


struct filesystem* fat16_init(){
    fat16_fs = (struct filesystem*)kzalloc(sizeof(struct filesystem));

    fat16_fs->resolve = fat16_resolve;
    fat16_fs->open = fat16_open;
    strcpy(fat16_fs->name,"FAT16");
    return fat16_fs;
};

int fat16_resolve(struct disk* disk){
    return 0;
}

void* fat16_open(struct disk* disk, struct path_part* path, FILE_MODE mode){
    return 0;
}