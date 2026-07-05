#include "pparser.h"
#include "string.h"
#include "kernel.h"
#include "kheap.h"
#include "status.h"
#include "memory.h"

static int pparser_path_valid_format(const char* filename){
    int len = strnlen(filename,PEACH_OS_MAX_PATH);
    return (len>=3 && is_digit(filename[0]) && memcmp(&filename[1],":/",2)==0);
}