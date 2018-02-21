#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

void save(uint16_t * memory, uint16_t * registers, int * memoryCursor);

void loadFromSave(uint16_t * memory, uint16_t * registers, int * memoryCursor);