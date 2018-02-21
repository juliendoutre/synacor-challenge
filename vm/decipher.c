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
    int test = sizeof(memory) / sizeof(uint16_t);
    int i = 0;
    int ID = 0;

    while (i < test)
    {
        fprintf(fp, "%d | ", ID);
        ID += 1;
        switch(memory[i])
        {
            case 0:
                fprintf(fp, "halt: ");
                i += 1;
                break;
            case 1:
                fprintf(fp, "set: ");
                i += 3;
                break;
            case 2:
                fprintf(fp, "push: ");
                i += 2;
                break;
            case 3:
                fprintf(fp, "pop: ");
                i += 2;
                break;
            case 4:
                fprintf(fp, "eq: ");
                i += 5;
                break;
            case 5:
                fprintf(fp, "gt: ");
                i += 5;
                break;
            case 6:
                fprintf(fp, "jmp: ");
                i += 2;
                break;
            case 7:
                fprintf(fp, "jt: ");
                i += 3;
                break;
            case 8:
                fprintf(fp, "jf: ");
                i += 3;
                break;
            case 9:
                fprintf(fp, "add: ");
                i += 4;
                break;
            case 10:
                fprintf(fp, "mult: ");
                i += 4;
                break;
            case 11:
                fprintf(fp, "mod: ");
                i += 4;
                break;
            case 12:
                fprintf(fp, "and: ");
                i += 4;
                break;
            case 13:
                fprintf(fp, "or: ");
                i += 4;
                break;
            case 14:
                fprintf(fp, "not: ");
                i += 3;
                break;
            case 15:
                fprintf(fp, "rmem: ");
                i += 3;
                break;
            case 16:
                fprintf(fp, "wmem: ");
                i += 3;
                break;
            case 17:
                fprintf(fp, "call: ");
                i += 2;
                break;
            case 18:
                fprintf(fp, "ret: ");
                i += 1;
                break;
            case 19:
                fprintf(fp, "out: ");
                i += 2;
                break;
            case 20:
                fprintf(fp, "in: ");
                i += 2;
                break;
            case 21:
                fprintf(fp, "noop: ");
                i += 1;
                break;
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
}