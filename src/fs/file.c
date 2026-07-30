#include "file.h"
#include "config.h"
#include "kernel.h"

struct filesystem* filesystems[PEACH_OS_MAX_FILE_SYSTEMS];
struct file_descriptor* file_descriptors[PEACH_OS_MAX_FILE_DESCRIPTORS];
