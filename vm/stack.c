#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stack.h"

Cell *push(uint16_t value, Cell *cursor)
{
    Cell *pointer = NULL;
    pointer = malloc(sizeof(Cell));
    pointer->value = value;
    pointer->previous = cursor;
    return pointer;
}

uint16_t pop(Cell **cursor)
{
    printf("cursor target: %p\n", *cursor);    
    uint16_t value = (*(*cursor)).value;
    free(*cursor);
    *cursor = (*(*cursor)).previous;
    printf("cursor target: %p\n", *cursor);    
    printf("%d\n", value);
    return value;
}