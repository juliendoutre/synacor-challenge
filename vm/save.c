#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "save.h"

void save(uint16_t * memory, uint16_t * registers, int * memoryCursor)
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
        fprintf(fp, "%d", registers[n]);
    }
    fclose(fp);
}

void loadFromSave(uint16_t * memory, uint16_t * registers, int * memoryCursor)
{
    
}