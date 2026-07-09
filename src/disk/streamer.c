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

int diskstreamer_read(struct disk_streamer* streamer, void* out, int total){
    int res = 0;

    

    return res;
}