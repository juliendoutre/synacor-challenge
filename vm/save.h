#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h"

void save(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell *stackCursor);

void loadFromSave(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell **stackCursor);