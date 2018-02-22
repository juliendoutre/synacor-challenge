#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct Cell Cell;

struct Cell {
    uint16_t value;
    struct Cell *previous;
};

Cell *push(uint16_t value, Cell *cursor);

uint16_t pop(Cell **cursor);