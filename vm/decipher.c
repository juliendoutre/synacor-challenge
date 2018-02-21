#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "utils.h"
#include "decipher.h"

void decipher(uint16_t *memory)
{
    FILE *fp;
    fp = fopen("sources.txt", "w");
    const int MEMORY_LENGTH = 32768;
    int i = 0;
    int ID = 0;

    uint16_t var1 = 0;
	uint16_t var2 = 0;
	uint16_t var3 = 0;

    while (i < MEMORY_LENGTH)
    {   
        if (i < MEMORY_LENGTH - 1)
	    {
		    var1 = memory[i + 1];
		    if (i < MEMORY_LENGTH - 2)
            {
                var2 = memory[i + 2];
                if (i < MEMORY_LENGTH - 3)
                {
                    var3 = memory[i + 3];
                }
            }
	    }

        switch(memory[i])
        {
            case 0:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "halt: ");
                i += 1;
                fprintf(fp, "\n");
                break;
            case 1:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "set: ");
                printVar(fp, var1);
                fprintf(fp, " = ");
                printVar(fp, var2);
                fprintf(fp, "\n");
                i += 3;
                break;
            case 2:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "push: push(");
                printVar(fp, var1);
                fprintf(fp, ");");
                fprintf(fp, "\n");
                i += 2;
                break;
            case 3:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "pop: ");
                printVar(fp, var1);
                fprintf(fp, " = pop();");
                i += 2;
                fprintf(fp, "\n");
                break;
            case 4:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "eq: if (");
                printVar(fp, var2);
                fprintf(fp, " == ");
                printVar(fp, var3);
                fprintf(fp, ") { ");
                printVar(fp, var1);
                fprintf(fp, " == 1 } else { ");
                printVar(fp, var1);
                fprintf(fp, " == 0 }");
                fprintf(fp, "\n");
                i += 5;
                break;
            case 5:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "gt: if (");
                printVar(fp, var2);
                fprintf(fp, " > ");
                printVar(fp, var3);
                fprintf(fp, ") { ");
                printVar(fp, var1);
                fprintf(fp, " == 1 } else { ");
                printVar(fp, var1);
                fprintf(fp, " == 0 }");
                fprintf(fp, "\n");
                i += 5;
                break;
            case 6:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "jmp: go to memory[");
                printVar(fp, var1);
                fprintf(fp, "]");
                fprintf(fp, "\n");
                i += 2;
                break;
            case 7:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "jt: if (");
                printVar(fp, var1);
                fprintf(fp, " != 0 { go to memory[");
                printVar(fp, var2);
                fprintf(fp, "] }");
                fprintf(fp, "\n");
                i += 3;
                break;
            case 8:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "jt: if (");
                printVar(fp, var1);
                fprintf(fp, " == 0 { go to ");
                printVar(fp, var2);
                fprintf(fp, " }");
                fprintf(fp, "\n");
                i += 3;
                break;
            case 9:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "add: ");
                printVar(fp, var1);
                fprintf(fp, " = ");
                printVar(fp, var2);
                fprintf(fp, " + ");
                printVar(fp, var3);
                fprintf(fp, "\n");
                i += 4;
                break;
            case 10:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "mult: ");
                printVar(fp, var1);
                fprintf(fp, " = ");
                printVar(fp, var2);
                fprintf(fp, " * ");
                printVar(fp, var3);
                fprintf(fp, "\n");
                i += 4;
                break;
            case 11:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "mod: ");
                printVar(fp, var1);
                fprintf(fp, " = ");
                printVar(fp, var2);
                fprintf(fp, " %% ");
                printVar(fp, var3);
                fprintf(fp, "\n");
                i += 4;
                break;
            case 12:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "and: ");
                printVar(fp, var1);
                fprintf(fp, " = ");
                printVar(fp, var2);
                fprintf(fp, " and ");
                printVar(fp, var3);
                fprintf(fp, "\n");
                i += 4;
                break;
            case 13:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "or: ");
                printVar(fp, var1);
                fprintf(fp, " = ");
                printVar(fp, var2);
                fprintf(fp, " or ");
                printVar(fp, var3);
                fprintf(fp, "\n");
                i += 4;
                break;
            case 14:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "not: ");
                printVar(fp, var1);
                fprintf(fp, " = ~");
                printVar(fp, var2);
                fprintf(fp, "\n");
                i += 3;
                break;
            case 15:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "rmem: ");
                printVar(fp, var1);
                fprintf(fp, " = memory[");
                printVar(fp, var2);
                fprintf(fp, "]");
                fprintf(fp, "\n");
                i += 3;
                break;
            case 16:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "wmem: memory[");
                printVar(fp, var1);
                fprintf(fp, "] = ");
                printVar(fp, var2);
                fprintf(fp, "\n");
                i += 3;
                break;
            case 17:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "call: push(");
                printVar(fp, i + 2);
                fprintf(fp, ");\n");
                fprintf(fp, "go to memory[");
                printVar(fp, var1);
                fprintf(fp, "]");
                fprintf(fp, "\n");
                i += 2;
                break;
            case 18:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "ret: go to memory[pop()];");
                fprintf(fp, "\n");
                i += 1;
                break;
            case 19:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "out: printf(");
                printVar(fp, var1);
                fprintf(fp, ");");
                fprintf(fp, "\n");
                i += 2;
                break;
            case 20:
                fprintf(fp, "%d | ", ID);
                ID += 1;
                fprintf(fp, "in: ");
                printVar(fp, var1);
                fprintf(fp, " = getchar();");
                fprintf(fp, "\n");
                i += 2;
                break;
            default:
                i += 1;
                break;
        }
    }
    fclose(fp);
}

void printVar(FILE *fp, uint16_t a)
{
    if (a < 32768)
    {
        fprintf(fp, "%d", a);
    }
    else 
    {
        fprintf(fp, "r%d", a % 32768);
    }
}