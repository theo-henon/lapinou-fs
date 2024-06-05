#include "output.h"

#define SECTOR_SIZE 512

bool file_mdwrite(const struct file *file, FILE *out)
{
    fwrite(file->name, sizeof(char), FILE_NAME_SIZE, out);
    fprintf(out, "%020zu%020zu", file->size, file->offset);
    fwrite(file->owner, sizeof(char), OWNER_NAME_SIZE, out);
    fprintf(out, "%020zu", file->children->size);
    const int n = 512 - (FILE_NAME_SIZE + OWNER_NAME_SIZE + 60);
    for (int i = 0; i < n; i++)
        fputc('\0', out);


    for (size_t i = 0; i < file->children->size; i++)
        file_mdwrite(file_getchild(file, i), out);
    return true;
}

bool volume_write(const struct volume *vol, FILE *out)
{
    fwrite(vol->version, sizeof(char), VOLUME_VERSION_SIZE, out);
    fprintf(out, "%020zu", vol->capacity);
    fprintf(out, "%020zu", file_nodec(vol->root));
    const int n = 512 - (VOLUME_VERSION_SIZE + 40);
    for (int i = 0; i < n; i++)
        fputc('\0', out);

    file_mdwrite(vol->root, out);

    return true;
}