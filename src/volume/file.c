#include "file.h"

#include <stdlib.h>
#include <string.h>

struct file *file_create(const char *name, size_t size, const char *owner,
                         bool is_dir)
{
    struct file *file = malloc(sizeof(struct file));
    if (file != NULL)
    {
        strncpy(file->name, name, FILE_NAME_SIZE);
        file->size = size;
        strncpy(file->owner, owner, OWNER_NAME_SIZE);
        file->is_dir = is_dir;
    }
    return file;
}

void file_free(struct file *file)
{
    free(file);
}
