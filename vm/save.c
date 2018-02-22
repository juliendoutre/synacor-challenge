#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "save.h"

void save(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell *stackCursor)
{
    FILE *fp;
    fp = fopen("save.txt", "w");
    const int MEMORY_LENGTH = 32768;
    for (int i=0;i<MEMORY_LENGTH;i++)
    {
        fprintf(fp, "%d ", memory[i]);
    }
    fprintf(fp, "\n");
    fprintf(fp, "%d\n", *memoryCursor);
    for (int n=0;n<8;n++)
    {
        fprintf(fp, "%d ", registers[n]);
    }
	fprintf(fp, "\n");
    while(stackCursor->previous != NULL)
    {
        fprintf(fp, " %d", stackCursor->value);
        stackCursor = stackCursor->previous;
    }
    fclose(fp);
}

void loadFromSave(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell **stackCursor)
{
    FILE *fp;
    fp = fopen("save.txt", "r");
	uint16_t a = 0;
	int b = 0;
    const int MEMORY_LENGTH = 32768;
	for (int i=0;i<MEMORY_LENGTH;i++)
	{
		fscanf(fp, "%hu", &a);
		memory[i] = a;
	}
	fscanf(fp, "%d", &b);
	*memoryCursor = b;
	for (int i=0;i<8;i++)
	{
		fscanf(fp, "%hu", &a);
		registers[i] = a;
	}
	while ((*stackCursor)->previous != NULL)
	{
		int value = pop(stackCursor);
	}

	Cell TemporaryStack = {0, NULL};
	Cell *TemporaryStackCursor = NULL;
	TemporaryStackCursor = &TemporaryStack;

	while (!feof(fp))
	{
		fscanf(fp, "%hu", &a);
		TemporaryStackCursor = push(a, TemporaryStackCursor);
	}
	while (TemporaryStackCursor->previous != NULL)
	{
		*stackCursor = push(pop(&TemporaryStackCursor), *stackCursor);
	}
    fclose(fp);
}