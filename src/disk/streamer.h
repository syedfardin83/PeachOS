#ifndef STREAMER_H
#define STREAMER_H

#include <stdint.h>

#include "disk.h"

struct disk_streamer{
    int pos;
    struct disk* disk;
};

struct disk_streamer* diskstreamer_new(int drive_id);
int diskstreamer_seek(struct disk_streamer* streamer, int pos);
int diskstreamer_read(struct disk_streamer* streamer, void* out, int total);


#endif