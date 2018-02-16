#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utils.h"
#include "stack.h"

int read(int memoryCursor, uint16_t *memory, uint16_t *registers, uint16_t *stack, const int STACK_LENGTH, bool *on, int *stackCursor)
{
	uint16_t head = memory[memoryCursor];
	uint16_t var1 = 0;
	uint16_t var2 = 0;
	uint16_t var3 = 0;

	const int MEMORY_LENGTH = sizeof(memory) / sizeof(uint16_t);
	
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

	switch (head) {
		case 0: // halt 
			*on = false;
			printf("\n The program was ended.\n");
			return 0;
			break;
		
		case 1: // set
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			registers[var1] = readVariable(var2, registers);
			return memoryCursor + 3;
			break;
		case 2: // push
			var1 = memory[memoryCursor + 1];
			if (*stackCursor == STACK_LENGTH - 1)
			{
				printf("Stack overflow.\n");
				*on = false;
				return 0;
				break;
			}
			else
			{
				*stackCursor += 1;
				stack[*stackCursor] = readVariable(var1, registers);
				return memoryCursor + 2;
				break;
			}
		case 3: // pop
			if (*stackCursor == -1)
			{
				printf("Error: stack is empty.\n");
				*on = false;
				return 0;
				break;
			}
			else
			{
				var1 = memory[memoryCursor + 1] % 32768;
				registers[var1] = stack[*stackCursor];
				*stackCursor--;
				return memoryCursor + 2;
			}
			break;
		case 4: // eq
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
			var1 = memory[memoryCursor + 1];
			return readVariable(var1, registers);
			break;
		case 7: // jt
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
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = (readVariable(var2, registers) + readVariable(var3, registers)) % 32768;
			return memoryCursor + 4;
			break;
		case 10: // mult
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = (readVariable(var2, registers) * readVariable(var3, registers)) % 32768;
			return memoryCursor + 4;
			break;
		case 11: // mod
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = (readVariable(var2, registers) % readVariable(var3, registers)) % 32768;
			return memoryCursor + 4;
			break;
		case 12: // and
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = readVariable(var2, registers) & readVariable(var3, registers);
			return memoryCursor + 4;
			break;
		case 13: // or
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			var3 = memory[memoryCursor + 3];
			registers[var1] = readVariable(var2, registers) | readVariable(var3, registers);
			return memoryCursor + 4;
			break;
		case 14: // not
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			registers[var1] = ~readVariable(var2, registers);
			return memoryCursor + 3;
			break;
		case 15: // rmem
			var1 = memory[memoryCursor + 1] % 32768;
			var2 = memory[memoryCursor + 2];
			registers[var1] = readVariable(var2, registers);
			return memoryCursor + 3;
			break;
		case 16: // wmem 
			var1 = memory[memoryCursor + 1];
			var2 = memory[memoryCursor + 2];
			memory[readVariable(var1, registers)] = readVariable(var2, registers);
			return memoryCursor + 3;
			break;
		case 17: // call
			if (*stackCursor == STACK_LENGTH - 1)
			{
				printf("Stack overflow.\n");
				*on = false;
				return 0;
				break;
			}
			else
			{	
				var1 = memory[memoryCursor + 1];
				var2 = memoryCursor + 2;
				*stackCursor += 1;
				stack[*stackCursor] = var2 ;
				return readVariable(var1, registers);
				break;
			}
			break;
		case 18: // ret
			if (*stackCursor == -1)
			{
				printf("Error: stack is empty.\n");
				*on = false;
				return 0;
				break;
			}
			else
			{
				var1 = stack[*stackCursor];
				*stackCursor--;
				return var1;
				break;
			}
		case 19: // out
			var1 = memory[memoryCursor + 1];		
			printf("%c", var1);
			return memoryCursor + 2;
			break;
		case 20: // in
			var1 = memory[memoryCursor + 1] % 32768;		
			registers[var1] = getchar();
			return memoryCursor + 2;
			break;
		case 21: // noop
			return memoryCursor + 1;
			break;
	}
}

uint16_t readVariable(uint16_t var, uint16_t *registers)
{
	if (var < 32768)
	{
		return var;
	}
	else
	{
		return registers[var % 32768];
	}
}

int load(uint16_t *memoire, int length)
{
	FILE *fp;

	if ((fp = fopen("../challenge.bin", "rb")) == NULL)
	{
		return -1;
	}
	else
	{	
		fread(memoire, length, 2, fp);
	}
	fclose(fp);
	return 0;
}

void showMemory(uint16_t *memoire, int length)
{
	for (int n=0;n<length;n++)
	{
		printf("adresse: %pn, | ", &memoire[n]);
		printf("instruction: %d\n", memoire[n] % 32768);
	}
}

void showRegisters(uint16_t *registers, int length)
{
	for (int n=0;n<length;n++)
	{
		printf("register n°%d", n);
		printf(" value: %d\n", registers[n]);
	}
}