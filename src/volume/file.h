#ifndef FILE_H
#define FILE_H

#define FILE_NAME_SIZE 128
#define OWNER_NAME_SIZE 32

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

#include "utils/vector.h"

struct file
{
    char name[FILE_NAME_SIZE];
    size_t size;
    size_t offset;
    char owner[OWNER_NAME_SIZE];
    bool is_dir;
    struct vector *children;
};

struct file *file_create(const char *name, size_t size, size_t offset,
                         const char *owner, bool is_dir);
const struct file *file_addchild(struct file *parent, struct file *child);
bool file_delchild(struct file *parent, size_t index);
const struct file *file_getchild(const struct file *parent, size_t index);
bool file_isreg(const struct file *file);
size_t file_nodec(const struct file *file);
size_t file_recsize(const struct file *file);
void file_free(struct file *file);

#endif // FILE_H
