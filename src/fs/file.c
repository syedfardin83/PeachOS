#include "file.h"
#include "config.h"
#include "kernel.h"
#include "status.h"

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
    //fs_insert_filesystem(fat16_init());
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

