#include "output.h"

bool volume_write(const struct volume *vol, FILE *out)
{
    fwrite(vol->version, sizeof(char), VOLUME_VERSION_SIZE, out);
    fprintf(out, "%020zu", vol->capacity);
    fprintf(out, "%020zu", file_nodec(vol->root));
    const int n = 512 - (VOLUME_VERSION_SIZE + 40);
    for (int i = 0; i < n; i++)
        fputc('\0', out);

    return true;
}