#include <stdlib.h>

#include "io/input.h"
#include "io/output.h"

int main(void)
{
    struct volume *vol = volume_create("lfsv1.00", 8192);
    file_addchild(vol->root, file_create("first_file", 0, 0, "me", false));

    FILE *vol_file = fopen("volume.lfs", "w+");
    volume_write(vol, vol_file);
    volume_free(vol);

    fseek(vol_file, 0, SEEK_SET);
    vol = volume_read(vol_file);
    if (vol != NULL)
    {
        printf("Filesystem version: %.*s\n", VOLUME_VERSION_SIZE, vol->version);
        printf("Capacity: %zu bytes\n", vol->capacity);
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
