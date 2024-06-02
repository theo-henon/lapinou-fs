#include "input.h"

#define SECTOR_SIZE 512
#define SIZE_T_LENGTH 20

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct volume *volume_read(FILE *in)
{
    char sector[SECTOR_SIZE];
    size_t readed = fread(sector, sizeof(char), SECTOR_SIZE, in);
    if (readed < SECTOR_SIZE)
        return NULL;

    char version[VOLUME_VERSION_SIZE] = { 0 };
    strncpy(version, sector, VOLUME_VERSION_SIZE);

    char capacity_str[SIZE_T_LENGTH + 1];
    strncpy(capacity_str, sector + VOLUME_VERSION_SIZE, SIZE_T_LENGTH);
    char *endptr = NULL;
    errno = 0;
    size_t capacity = strtoull(capacity_str, &endptr, 10);
    if (errno == ERANGE)
        return NULL;

    return volume_create(version, capacity);
}