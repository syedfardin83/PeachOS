#ifndef PPARSER_H
#define PPARSER_H

#include <stdbool.h>

struct path_root{
    int driver_no;
    struct path_part* first;
};

struct path_part{
    const char* part;
    struct path_part* next;
};

static int pparser_path_valid_format(const char* filename);

#endif