#include "file.h"
#include "config.h"
#include "kernel.h"
#include "status.h"
#include "kheap.h"
#include "disk.h"
#include "memory.h"
#include "fat16.h"

struct filesystem* filesystems[PEACH_OS_MAX_FILE_SYSTEMS];
struct file_descriptor* file_descriptors[PEACH_OS_MAX_FILE_DESCRIPTORS];

struct filesystem** fs_get_free_filesystem(){
    for(int i=0;i<PEACH_OS_MAX_FILE_SYSTEMS;i++){
        if(filesystems[i]==0) return &filesystems[i];
    }
    return 0;
}

void fs_insert_filesystem(struct filesystem* filesystem){
    struct filesystem** free_fs;
    free_fs = fs_get_free_filesystem();
    if(!free_fs){
        print("\nError: Inserting fileystem unsuccessful");
        while(1);
    }

    *free_fs = filesystem;
}

static void fs_static_load()
{
    fs_insert_filesystem(fat16_init());
}

void fs_load()
{
    memset(filesystems, 0, sizeof(filesystems));
    fs_static_load();
}

void fs_init()
{
    memset(file_descriptors, 0, sizeof(file_descriptors));
    fs_load();
}

static int fs_new_file_descriptor(struct file_descriptor** desc_out){
    int res = -ENOMEM;
    for(int i=0;i<PEACH_OS_MAX_FILE_DESCRIPTORS;i++){
        if(file_descriptors[i]==0){
            //  Creating the new file descriptor
            struct file_descriptor* desc = kzalloc(sizeof(struct file_descriptor));
            file_descriptors[i]=desc;
            desc->index = i+1;
            desc_out = &file_descriptors[i];
            res=0;
            break;
        }
    }

    return res;
}

static struct file_descriptor* fs_get_file_descriptor(int desc_no){
    if(desc_no<=0 || desc_no>PEACH_OS_MAX_FILE_DESCRIPTORS) return 0;

    return file_descriptors[desc_no-1];
}

//  Checks the type of filesystem used by a drive
struct filesystem* fs_resolve(struct disk* disk){
    struct filesystem* fs = 0;
    for(int i=0;i<PEACH_OS_MAX_FILE_SYSTEMS;i++){
        if(filesystems[i]!=0 && filesystems[i]->resolve(disk)==0){
            fs=filesystems[i];
            break;
        }
    }
    return fs;
}

int fopen(const char* filename, const char* mode){
    return -EIO;
}