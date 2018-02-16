#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h"

struct Cell {
    uint16_t value;
    uint16_t *next;
};