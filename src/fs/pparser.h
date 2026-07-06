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

struct path_root* pparser_parse(const char* path, const char* current_directory_path);
void pparser_free(struct path_root* root);

#endif