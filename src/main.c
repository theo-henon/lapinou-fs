#include "io/output.h"

int main(void)
{
    struct volume *vol = volume_create("lfs1.0", 1024 * 1024 * 1024);
    if (vol != NULL)
    {
        bool success = volume_write(vol, stdout);
        volume_free(vol);
        return !success;
    }
    else
        return 1;
}
