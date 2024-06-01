#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdbool.h>
#include <stdio.h>

#include "volume/volume.h"

bool volume_write(const struct volume *vol, FILE *out);

#endif // OUTPUT_H
