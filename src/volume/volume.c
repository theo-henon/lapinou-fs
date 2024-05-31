#include "volume.h"

#include <stdlib.h>

void volume_free(struct volume *vol)
{
    file_free(vol->root);
    free(vol);
}