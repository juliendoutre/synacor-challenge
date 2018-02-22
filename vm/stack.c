#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h"

Cell *push(uint16_t value, Cell *cursor)
{
    // create a new cell with the given value and return a pointer to this new cell
    Cell *pointer = NULL;
    pointer = malloc(sizeof(Cell));
    pointer->value = value;
    pointer->previous = cursor;
    return pointer;
}

uint16_t pop(Cell **cursor)
{
    // return the value of the top cell of the stack
    uint16_t value = (*cursor)->value;
    free(*cursor);
    *cursor = (*cursor)->previous;
    return value;
}