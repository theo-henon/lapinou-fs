#ifndef FILE_H
#define FILE_H

#define FILE_NAME_SIZE 128
#define OWNER_NAME_SIZE 32

#include <stdbool.h>
#include <stddef.h>
#include <sys/types.h>

struct file
{
    char name[FILE_NAME_SIZE];
    size_t size;
    char owner[OWNER_NAME_SIZE];
    bool is_dir;
};

struct file *file_create(const char *name, size_t size, const char *owner,
                         bool is_dir);
void file_free(struct file *file);

#endif // FILE_H
