#ifndef STREAMER_H
#define STREAMER_H

#include "disk.h"

struct disk_streamer{
    int pos;
    struct disk* disk;
}

#endif