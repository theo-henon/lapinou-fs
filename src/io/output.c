#include "output.h"

bool volume_write(const struct volume *vol, FILE *out)
{
    // Write volume header
    fwrite(vol->version, sizeof(char), VOLUME_VERSION_SIZE, out);
    fprintf(out, "%020zu", vol->capacity);
    fprintf(out, "%020zu", file_nodec(vol->root));
    return true;

    // TODO: Write files metadata

    // TODO: Write files data
}