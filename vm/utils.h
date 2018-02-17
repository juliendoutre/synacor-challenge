#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int read(int memoryCursor, uint16_t *memory, uint16_t *registers, uint16_t *stack, const int STACK_LENGTH, bool *on, int *stackCursor);

uint16_t readVariable(uint16_t var, uint16_t *registers);

int load(uint16_t *memoire, int length);

void showMemory(uint16_t *memoire, int length);

void showRegisters(uint16_t *registers, int length);