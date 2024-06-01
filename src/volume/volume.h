#ifndef VOLUME_H
#define VOLUME_H

#define VOLUME_VERSION_SIZE 8

#include "file.h"

struct volume
{
    char version[VOLUME_VERSION_SIZE];
    size_t capacity;
    struct file *root;
};

struct volume *volume_create(const char *version, size_t capacity);
size_t volume_size(const struct volume *vol);
void volume_free(struct volume *vol);

#endif // VOLUME_H
