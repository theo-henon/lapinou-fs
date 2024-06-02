#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#include "volume/volume.h"

struct volume *volume_read(FILE *in);

#endif // INPUT_H
