#include "volume.h"

#include <stdlib.h>
#include <string.h>

struct volume *volume_create(const char *version, size_t capacity)
{
    struct volume *vol = calloc(1, sizeof(struct volume));
    if (vol != NULL)
    {
        strncpy(vol->version, version, VOLUME_VERSION_SIZE);
        vol->capacity = capacity;
        vol->root = file_create("/", 0, 0, "me", true);
    }
    return vol;
}

size_t volume_size(const struct volume *vol)
{
    return file_recsize(vol->root);
}

void volume_free(struct volume *vol)
{
    file_free(vol->root);
    free(vol);
}