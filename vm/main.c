#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "utils.h"

int main(int argc, char *argv[]) {

	// Definition of some usefull variables and pointers
	bool on = true;
	int memoryCursor = 0;
	
	// Definition of the memory table
	const int MEMORY_LENGTH = 32768;
	uint16_t memory[MEMORY_LENGTH];

	// Definition of the registers
	const int REGISTERS_NUMBER = 8;
	uint16_t registers[REGISTERS_NUMBER];

	// Definition of the stack
	Cell Init = {0, NULL};
	Cell *stackCursor = NULL;
	stackCursor = &Init;

	// Load the program in the memory		
	if (load(memory, MEMORY_LENGTH) == 0)
	{
		printf("\nProgram successfully loaded.\n");
	}
	else
	{
		printf("Error: program not loaded.\n");
		on = false;
	}

	// Program loop
	while (memoryCursor < MEMORY_LENGTH == true && on == true)
	{
		memoryCursor = read(memoryCursor, memory, registers, &on, &stackCursor);
	}

	// Pause
	getchar(); 

	return 0;
}