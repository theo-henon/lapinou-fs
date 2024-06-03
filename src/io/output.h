#ifndef OUTPUT_H
#define OUTPUT_H

#include <stdbool.h>
#include <stdio.h>

#include "volume/volume.h"

bool file_mdwrite(const struct file *file, FILE *out);
bool volume_write(const struct volume *vol, FILE *out);

#endif // OUTPUT_H
