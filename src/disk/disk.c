#include "io.h"
#include "disk.h"
#include "memory.h"
#include "config.h"
#include "status.h"

struct disk disk;

int disk_read_sector(int lba, int total, void* buf){
    if (total <= 0 || total > 256) {
        return -EIO;
    }

    while (insb(0x1f7) & 0x80) {
    }

    outb(0x1f6, 0xE0 | ((lba >> 24) & 0x0F));
    outb(0x1f2, total == 256 ? 0 : (unsigned char)total);
    outb(0x1f3,(unsigned char)(lba & 0xff));
    outb(0x1f4,(unsigned char)((lba >> 8) & 0xFF));
    outb(0x1f5,(unsigned char)((lba >> 16) & 0xFF));
    outb(0x1f7,0x20);

    unsigned short *ptr = (unsigned short *)buf;

    for(int i=0;i<total;i++){
        unsigned char c = insb(0x1f7);
        while(!(c&0x08)){
            if (c & 0x01) {
                return -EIO;
            }
            c = insb(0x1f7);
        }

        for(int j=0;j<256;j++){
            *ptr = insw(0x1f0);
            ptr++;
        }
    }

    return 0;
}

void disk_search_and_init(){
    memset(&disk, 0, sizeof(disk));
    disk.sector_size=PEACH_OS_SECTOR_SIZE;
    disk.type=PEACH_OS_DISK_TYPE_REAL;
}

struct disk* disk_get(int index){
    if(index!=0) return 0;
    return &disk;
}

int disk_read_block(struct disk* idisk, unsigned int lba, int total, void* buf){
    if(idisk!=&disk) return -EIO;
    return disk_read_sector(lba, total, buf);
}