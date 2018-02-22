#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "save.h"

void save(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell *stackCursor)
{
	// save the memory, the cursor in the memory, the registers and the stack into a file
	
	// file creation
    FILE *fp;
    fp = fopen("save.txt", "w");
    const int MEMORY_LENGTH = 32768;
	
	// write the memory values
    for (int i=0;i<MEMORY_LENGTH;i++)
    {
        fprintf(fp, "%d ", memory[i]);
    }
    fprintf(fp, "\n");

	// write the memoryCursor value
    fprintf(fp, "%d\n", *memoryCursor);

	// write the registers values
    for (int n=0;n<8;n++)
    {
        fprintf(fp, "%d ", registers[n]);
    }
	fprintf(fp, "\n");

	// write the stack values
    while(stackCursor->previous != NULL)
    {
        fprintf(fp, " %d", stackCursor->value);
        stackCursor = stackCursor->previous;
    }
    fclose(fp);
}

void loadFromSave(uint16_t * memory, uint16_t * registers, int * memoryCursor, Cell **stackCursor)
{
	// load a saved game (memory, memoryCursor, registers and stack) from save.txt

	// open the file
    FILE *fp;
    fp = fopen("save.txt", "r");
	uint16_t a = 0;
	int b = 0;
    const int MEMORY_LENGTH = 32768;

	// load memory
	for (int i=0;i<MEMORY_LENGTH;i++)
	{
		fscanf(fp, "%hu", &a);
		memory[i] = a;
	}

	// load memoryCursor
	fscanf(fp, "%d", &b);
	*memoryCursor = b;
	for (int i=0;i<8;i++)
	{
		fscanf(fp, "%hu", &a);
		registers[i] = a;
	}

	// make the stack empty
	while ((*stackCursor)->previous != NULL)
	{
		int value = pop(stackCursor);
	}

	// initialization of an empty temporary stack
	Cell TemporaryStack = {0, NULL};
	Cell *TemporaryStackCursor = NULL;
	TemporaryStackCursor = &TemporaryStack;

	// fill the temporary stack with stack values stored in the file (due to the stack construction there are stored backward)
	while (!feof(fp))
	{
		fscanf(fp, "%hu", &a);
		TemporaryStackCursor = push(a, TemporaryStackCursor);
	}

	// pop all the temporary stack to fill the stack and obtain the same order as in the saved game stack
	while (TemporaryStackCursor->previous != NULL)
	{
		*stackCursor = push(pop(&TemporaryStackCursor), *stackCursor);
	}
    fclose(fp);
}