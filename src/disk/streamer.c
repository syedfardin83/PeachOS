#include "streamer.h"
#include "kheap.h"
#include "config.h"

struct disk_streamer* diskstreamer_new(int drive_id){
    struct disk_streamer* streamer = kzalloc(sizeof(struct disk_streamer));
    streamer->pos = 0;

    struct disk* disk = disk_get(drive_id);
    if(!disk) return 0;
    streamer->disk = disk;

    return streamer;
}

int diskstreamer_seek(struct disk_streamer* streamer, int pos){
    streamer->pos = pos;
    return 0;
}

static uint32_t required_sectors(uint32_t bytes){
    if((bytes%PEACH_OS_SECTOR_SIZE)==0) return bytes/PEACH_OS_SECTOR_SIZE;
    return ((int)(bytes/PEACH_OS_SECTOR_SIZE)) + 1;
}

int diskstreamer_read(struct disk_streamer* streamer, void* out, int total){
    int res = 0;

    int lba = streamer->pos/PEACH_OS_SECTOR_SIZE;
    int sectors = required_sectors(total);
    // char buf[sectors*PEACH_OS_SECTOR_SIZE];
    char* buf = (char*)kzalloc(sectors*PEACH_OS_SECTOR_SIZE);

    res = disk_read_sector(lba, sectors, (void*)buf);

    char *ptr = (char*)out;
    int offset = streamer->pos%PEACH_OS_SECTOR_SIZE;
    for(int i=0;i<total;i++){
        *(ptr++) = *(buf+i+offset);
    }
    kfree(buf);
    streamer->pos += total;
    return res;
}