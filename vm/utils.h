#pragma once
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include "save.h"
#include "decipher.h"

int read(int memoryCursor, uint16_t *memory, uint16_t *registers, bool *on, Cell **stackCursor);

uint16_t readVariable(uint16_t var, uint16_t *registers);

int load(uint16_t *memory, int length);

void showMemory(uint16_t *memory, int length);

void showRegisters(uint16_t *registers, int length);

void save(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell *stackCursor);

void loadFromSave(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell **stackCursor);

void showStack(Cell *stackCursor);