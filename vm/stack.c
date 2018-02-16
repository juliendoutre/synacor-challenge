#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h"

struct Cell {
    uint16_t value;
    struct Cell *next;
};

