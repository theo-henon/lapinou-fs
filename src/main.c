#include <stdlib.h>

#include "io/input.h"
#include "io/output.h"

static void file_print(const struct file *file, unsigned depth)
{
    if (file == NULL)
        return;

    for (unsigned i = 0; i < depth; i++)
        printf("  ");
    //printf("- '%.*s': %zu bytes, %zu bytes, %.*s\n", FILE_NAME_SIZE, file->name, file->size, file->offset, OWNER_NAME_SIZE, file->owner);

    printf("%zu\n", file->children->size);
    for (size_t i = 0; i < file->children->size; i++)
        file_print(file_getchild(file, i), depth + 1);
}

int main(void)
{
    struct volume *vol = volume_create("lfsv1.00", 8192);
    file_addchild(vol->root, file_create("first_file", 0, 0, "me", false));
    file_addchild(vol->root, file_create("second_file", 0, 0, "me", false));

    FILE *vol_file = fopen("volume.lfs", "w+");
    volume_write(vol, vol_file);
    volume_free(vol);

    fseek(vol_file, 0, SEEK_SET);
    vol = volume_read(vol_file);
    if (vol != NULL)
    {
        //printf("Filesystem version: %.*s\n", VOLUME_VERSION_SIZE, vol->version);
        //printf("Capacity: %zu bytes\n", vol->capacity);
        //printf("File count: %zu\n", file_nodec(vol->root));
        file_print(vol->root, 0);
        volume_free(vol);
        fclose(vol_file);
    }
    else
    {
        fclose(vol_file);
        fprintf(stderr, "Invalid volume '%s'\n", "volume.lfs");
        return 1;
    }

    return 0;
}
