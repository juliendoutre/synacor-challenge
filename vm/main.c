#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "utils.h"
#include "stack.h"

int main(int argc, char *argv[]) {

	// Welcome
	printf("Hello world, I'm a Virtual Machine !\n");

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

	const int STACK_LENGTH = 10000;
	uint16_t stack[STACK_LENGTH];
	int stackCursor = -1;

	// Load the program in the memory		
	if (load(memory, MEMORY_LENGTH) == 0)
	{
		printf("\nProgram successfully loaded.\n");
		showMemory(memory, MEMORY_LENGTH);
	}
	else
	{
		printf("Error: program not loaded.\n");
		on = false;
	}

	// Program loop
	while (memoryCursor < MEMORY_LENGTH == true && on == true)
	{
		memoryCursor = read(memoryCursor, memory, registers, stack, STACK_LENGTH, &on, &stackCursor);
		// showRegisters(registers, 8);
	}

	// Pause
	getchar(); 

	return 0;
}