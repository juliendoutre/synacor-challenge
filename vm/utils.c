#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "save.h"

int read(int memoryCursor, uint16_t *memory, uint16_t *registers, bool *on, Cell **stackCursor)
{
	// this function returns the adress of the next instruction to be executed after having executed the current instruction

	// variables for the instruction code and its arguments 
	uint16_t head = memory[memoryCursor];
	uint16_t var1 = 0;
	uint16_t var2 = 0;
	uint16_t var3 = 0;

	// variables for the debugger
	char cmd = ' ';
	char command[10] = "";

	const int MEMORY_LENGTH = 32768;
	
	// assign values to the arguments which can be defined
	if (memoryCursor < MEMORY_LENGTH - 1)
	{
		var1 = memory[memoryCursor + 1];
		if (memoryCursor < MEMORY_LENGTH - 2)
		{
			var2 = memory[memoryCursor + 2];
			if (memoryCursor < MEMORY_LENGTH - 3)
			{
				var3 = memory[memoryCursor + 3];
			}
		}
	}

	// opcode test
	switch (head) {
		case 0: // halt 
			// stop execution and terminate the program
			*on = false;
			printf("\n The program was ended.\n");
			return 0;
			break;
		
		case 1: // set
			// set register <a> to the value of <b>
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			registers[var1] = readVariable(var2, registers);
			return memoryCursor + 3;
			break;
		case 2: // push
			// push <a> onto the stack
			var1 = memory[memoryCursor + 1];
			*stackCursor = push(readVariable(var1, registers), *stackCursor);
			return memoryCursor + 2;
			break;
		case 3: // pop
			// remove the top element from the stack and write it into <a>; empty stack = error
			if ((*(*stackCursor)).previous == NULL)
			{
				printf("Error: stack is empty.\n");
				*on = false;
				return memoryCursor + 2;
				break;
			}
			else
			{
				var1 = memory[memoryCursor + 1] % 32768;
				registers[var1] = pop(stackCursor);
				return memoryCursor + 2;
			}
			break;
		case 4: // eq
			// set <a> to 1 if <b> is equal to <c>; set it to 0 otherwise
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			if (readVariable(var2, registers) == readVariable(var3, registers))
			{
				registers[var1] = 1;
			}
			else 
			{
				registers[var1] = 0;
			}
			return memoryCursor + 4;
			break;
		case 5: // gt
			// set <a> to 1 if <b> is greater than <c>; set it to 0 otherwise
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			if (readVariable(var2, registers) > readVariable(var3, registers))
			{
				registers[var1] = 1;
			}
			else 
			{
				registers[var1] = 0;
			}
			return memoryCursor + 4;
			break;
		case 6: // jmp
			// jump to <a>
			var1 = memory[memoryCursor + 1];
			return readVariable(var1, registers);
			break;
		case 7: // jt
			// if <a> is nonzero, jump to <b>
			var1 = memory[memoryCursor + 1];
			var2 = memory[memoryCursor + 2];
			if (readVariable(var1, registers) != 0)
			{
				return readVariable(var2, registers);
			}
			else
			{
				return memoryCursor + 3;
			}
			break;
		case 8: // jf
			// if <a> is zero, jump to <b>
			var1 = memory[memoryCursor + 1];
			var2 = memory[memoryCursor + 2];
			if (readVariable(var1, registers) == 0)
			{
				return readVariable(var2, registers);
			}
			else
			{
				return memoryCursor + 3;
			}
			break;
		case 9: // add
			// assign into <a> the sum of <b> and <c> (modulo 32768)
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = (readVariable(var2, registers) + readVariable(var3, registers)) % 32768;
			return memoryCursor + 4;
			break;
		case 10: // mult
			// store into <a> the product of <b> and <c> (modulo 32768)
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = (readVariable(var2, registers) * readVariable(var3, registers)) % 32768;
			return memoryCursor + 4;
			break;
		case 11: // mod
			// store into <a> the remainder of <b> divided by <c>
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = (readVariable(var2, registers) % readVariable(var3, registers)) % 32768;
			return memoryCursor + 4;
			break;
		case 12: // and
			// stores into <a> the bitwise and of <b> and <c>
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = readVariable(var2, registers) & readVariable(var3, registers);
			return memoryCursor + 4;
			break;
		case 13: // or
			// stores into <a> the bitwise or of <b> and <c>
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = readVariable(var2, registers) | readVariable(var3, registers);
			return memoryCursor + 4;
			break;
		case 14: // not
			// stores 15-bit bitwise inverse of <b> in <a>
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			registers[var1] = ~ readVariable(var2, registers) & ((1 << 15) - 1);
			return memoryCursor + 3;
			break;
		case 15: // rmem
			// read memory at address <b> and write it to <a>
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			registers[var1] = memory[readVariable(var2, registers)];
			return memoryCursor + 3;
			break;
		case 16: // wmem 
			// write the value from <b> into memory at address <a>
			var1 = memory[memoryCursor + 1];
			var2 = memory[memoryCursor + 2];
			memory[readVariable(var1, registers)] = readVariable(var2, registers);
			return memoryCursor + 3;
			break;
		case 17: // call
			// write the address of the next instruction to the stack and jump to <a>
			var1 = memory[memoryCursor + 1];
			var2 = memoryCursor + 2;
			*stackCursor = push(var2, *stackCursor);
			return readVariable(var1, registers);
			break;
		case 18: // ret
			// remove the top element from the stack and jump to it; empty stack = halt
			if ((*(*stackCursor)).previous == NULL)
			{
				printf("Error: stack is empty.\n");
				*on = false;
				return 0;
				break;
			}
			else
			{
				var1 = pop(stackCursor);
				return var1;
				break;
			}
		case 19: // out
			// write the character represented by ascii code <a> to the terminal
			var1 = readVariable(memory[memoryCursor + 1], registers);		
			printf("%c", var1);
			return memoryCursor + 2;
			break;
		case 20: // in
			var1 = memory[memoryCursor + 1] % 32768;
			cmd = getchar(); // test the first char to decide to launch or not the debugger
			if (cmd == '$') // debugger
			{
				scanf("%s", command);
				if (strcmp(command, "reg") == 0) // show registers values
				{
					showRegisters(registers, 8);
				}
				else if (strcmp(command, "chreg") == 0) // edit the value of a register
				{
					printf("reg to edit:");
					int sh;
					scanf("%d", &sh);
					printf("value:");
					int sh2;
					scanf("%d", &sh2);
					printf("\nDone.\n");
					registers[sh] = sh2;
				}
				else if (strcmp(command, "decip") == 0) // decipher challenge.bin into a readable file
				{
					decipher(memory);
					printf("\nDone.\n");
				}
				else if (strcmp(command, "save") == 0) // save the game into save.txt file
				{
					save(memory, registers, &memoryCursor, *stackCursor);
					printf("\nDone.\n");
				}
				else if (strcmp(command, "load") == 0) // load saved game
				{
					loadFromSave(memory, registers, &memoryCursor, stackCursor);
					printf("\nDone.\n");
				}
				else if (strcmp(command, "mem") == 0) // show the memory
				{
					showMemory(memory, MEMORY_LENGTH);
					printf("\nDone.\n");
				}
				else if (strcmp(command, "stack") == 0) // show the values in the stack
				{
					showStack(*stackCursor);
					printf("\nDone.\n");
				}
				else 
				{
					printf("\nunknow command.\n");
				}
				return memoryCursor;
			}
			else // read a character from the terminal and write its ascii code to <a>; it can be assumed that once input starts, it will continue until a newline is encountered; this means that you can safely read whole lines from the keyboard and trust that they will be fully read
			{
				registers[var1] = cmd;
				return memoryCursor + 2;
			}
			break;
		case 21: // noop
			// no operation
			return memoryCursor + 1;
			break;
	}
}

uint16_t readVariable(uint16_t var, uint16_t *registers)
{
	// return the value of an argument (stored in a register or hard-coded in the memory)
	if (var < 32768)
	{
		return var;
	}
	else
	{
		return registers[var % 32768];
	}
}

int load(uint16_t *memory, int length)
{
	// load challenge.bin in the memory array
	FILE *fp;

	if ((fp = fopen("challenge.bin", "rb")) == NULL)
	{
		return -1;
	}
	else
	{	
		fread(memory, length, 2, fp);
	}
	fclose(fp);
	return 0;
}

void showMemory(uint16_t *memory, int length)
{
	for (int n=0;n<length;n++)
	{
		printf("adresse: %pn, | ", &memory[n]);
		printf("instruction: %d\n", memory[n] % 32768);
	}
}

void showRegisters(uint16_t *registers, int length)
{
	printf("\n");
	for (int n=0;n<length;n++)
	{
		printf("register n°%d", n);
		printf(" value: %d\n", registers[n]);
	}
}

void showStack(Cell *stackCursor)
{
	Cell *cursor = NULL;
	cursor = stackCursor;
	printf("TOP\n");
	while (cursor->previous != NULL)
	{
		printf("%d\n", cursor->value);
		 cursor = cursor->previous;
	}
	printf("INIT\n");
}