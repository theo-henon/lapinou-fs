#include "input.h"

#define SECTOR_SIZE 512
#define SIZE_T_LENGTH 20

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct file *file_mdread(FILE *in)
{
    char sector[SECTOR_SIZE];
    size_t readed = fread(sector, sizeof(char), SECTOR_SIZE, in);
    if (readed < SECTOR_SIZE)
        return NULL;

    char name[FILE_NAME_SIZE] = { '\0' };
    strncpy(name, sector, FILE_NAME_SIZE);

    char size_str[SIZE_T_LENGTH + 1] = { '\0' };
    strncpy(size_str, sector + FILE_NAME_SIZE, SIZE_T_LENGTH);
    size_t size = strtoull(size_str, NULL, 10);

    char offset_str[SIZE_T_LENGTH + 1] = { '\0' };
    strncpy(offset_str, sector + FILE_NAME_SIZE + SIZE_T_LENGTH, SIZE_T_LENGTH);
    size_t offset = strtoull(offset_str, NULL, 10);

    char owner[OWNER_NAME_SIZE] = { '\0' };
    strncpy(owner, sector + FILE_NAME_SIZE + 2 * SIZE_T_LENGTH,
            OWNER_NAME_SIZE);

    char children_count_str[SIZE_T_LENGTH + 1] = { '\0' };
    strncpy(children_count_str,
            sector + FILE_NAME_SIZE + 2 * SIZE_T_LENGTH + OWNER_NAME_SIZE,
            SIZE_T_LENGTH);
    size_t children_count = strtoull(children_count_str, NULL, 10);

    struct file *file =
        file_create(name, size, offset, owner, children_count > 0);
    for (size_t i = 0; i < children_count; i++)
    {
        struct file *child = file_mdread(in);
        if (child == NULL)
        {
            file_free(file);
            return NULL;
        }
        file_addchild(file, child);
    }

    return file;
}

struct volume *volume_read(FILE *in)
{
    char sector[SECTOR_SIZE];
    size_t readed = fread(sector, sizeof(char), SECTOR_SIZE, in);
    if (readed < SECTOR_SIZE)
        return NULL;

    char version[VOLUME_VERSION_SIZE] = { '\0' };
    strncpy(version, sector, VOLUME_VERSION_SIZE);

    char capacity_str[SIZE_T_LENGTH + 1];
    strncpy(capacity_str, sector + VOLUME_VERSION_SIZE, SIZE_T_LENGTH);
    size_t capacity = strtoull(capacity_str, NULL, 10);

    struct file *root = file_mdread(in);
    if (root != NULL)
    {
        struct volume *vol = volume_create(version, capacity);
        if (vol != NULL)
        {
            vol->root = root;
            return vol;
        }
        return NULL;
    }
    else
        return NULL;
}