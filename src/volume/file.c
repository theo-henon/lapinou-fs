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
        file->children = vector_create(1, sizeof(struct file *));
    }
    return file;
}

bool file_delchild(struct file *parent, size_t index)
{
    return vector_pop(parent->children, index);
}

const struct file *file_addchild(struct file *parent, struct file *child)
{
    if (file_isreg(parent))
        return NULL;

    if (vector_pushback(parent->children, &child))
        return child;
    return NULL;
}

bool file_isreg(const struct file *file)
{
    return !file->is_dir;
}

size_t file_nodec(const struct file *file)
{
    if (file == NULL)
        return 0;

    size_t count = 1;
    if (file->is_dir && file->children != NULL)
        for (size_t i = 0; i < file->children->size; i++)
            count += file_nodec(vector_get(file->children, i));
    return count;
}

size_t file_recsize(const struct file *file)
{
    if (file == NULL)
        return 0;
    if (!file->is_dir)
        return file->size;

    size_t size = 0;
    for (size_t i = 0; i < file->children->size; i++)
        size += file_recsize(vector_get(file->children, i));
    return size;
}

void file_free(struct file *file)
{
    vector_free(file->children);
    free(file);
}
