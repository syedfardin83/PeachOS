#include "pparser.h"
#include "string.h"
#include "kernel.h"
#include "kheap.h"
#include "status.h"
#include "memory.h"

static int pparser_path_valid_format(const char* filename){
    int len = strnlen(filename,PEACH_OS_MAX_PATH);
    return (len>=3 && is_digit(filename[0]) && memcmp((void*)&filename[1],":/",2)==0);
}

static int pparser_get_drive_by_path(const char** ptr){
    
    if(!pparser_path_valid_format(*ptr)) return -EBADPATH;

    int drive_no = to_numeric_digit(*ptr[0]);

    *ptr += 3;

    return drive_no;

}

static struct path_root* pparser_create_path_root(int drive_no){
    struct path_root* path_r = (struct path_root*)kzalloc(sizeof(struct path_root));
    path_r->driver_no = drive_no;
    path_r->first = 0;
    return path_r;
}

static const char* pparser_get_path_part(const char** ptr){
    int i = 0;
    char* result_path = kzalloc(PEACH_OS_MAX_PATH);
    while(**ptr!='/' && **ptr!='\0'){
        result_path[i]=**ptr;
        *ptr+=1;
        i++;
    }

    if(**ptr=='/') *ptr+=1;
    
    if(i==0){
        kfree(result_path);
        result_path=0;
    }

    return result_path;
}

struct path_part* pparser_parse_path_part(struct path_part* last_part, const char** path){
    const char* path_part_str = pparser_get_path_part(path);

    if(!path_part_str) return 0;

    struct path_part* new_part = kzalloc(sizeof(struct path_part));

    new_part->part = path_part_str;
    new_part->next = 0x00;

    if(last_part){
        last_part->next = new_part;
    }

    return new_part;
}

void pparser_free(struct path_root* root){
    struct path_part* curr_part = root->first;
    while(curr_part){
        struct path_part* next = curr_part->next;
        kfree(curr_part->next);
        kfree(curr_part);
        curr_part=next; 
    }

    kfree(root);
}

struct path_root* pparser_parse(const char* path, const char* current_directory_path){
    int res = 0;
    const char* tmp_path = path;
    struct path_root* path_root = 0;

    if (strlen(path) > PEACH_OS_MAX_PATH)
    {
        goto out;
    }

    res = pparser_get_drive_by_path(&tmp_path);
    if (res < 0)
    {
        goto out;
    }

    path_root = pparser_create_path_root(res);
    if (!path_root)
    {
        goto out;
    }

    struct path_part* first_part = pparser_parse_path_part(NULL, &tmp_path);
    if (!first_part)
    {
        goto out;
    }

    path_root->first = first_part;
    struct path_part* part = pparser_parse_path_part(first_part, &tmp_path);
    while(part)
    {
        part = pparser_parse_path_part(part, &tmp_path);
    }
    
out:
    return path_root;
}

