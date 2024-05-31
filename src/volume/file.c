#include "file.h"

#include <stdlib.h>
#include <string.h>

struct file *file_create(const char *name, size_t size, size_t offset,
                         const char *owner, bool is_dir)
{
    struct file *file = malloc(sizeof(struct file));
    if (file != NULL)
    {
        strncpy(file->name, name, FILE_NAME_SIZE);
        file->size = size;
        file->offset = offset;
        strncpy(file->owner, owner, OWNER_NAME_SIZE);
        file->is_dir = is_dir;
        file->children = vector_create(1, sizeof(struct file));
    }
    return file;
}

bool file_delchild(struct file *parent, size_t index)
{
    return vector_pop(parent->children, index);
}

const struct file *file_addchild(struct file *parent, const struct file *child)
{
    if (file_isreg(parent))
        return NULL;

    if (vector_pushback(parent->children, child))
        return child;
    return NULL;
}

bool file_isreg(const struct file *file)
{
    return !file->is_dir;
}

void file_free(struct file *file)
{
    vector_free(file->children);
    free(file);
}
