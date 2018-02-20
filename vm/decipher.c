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
    const int MEMORY_LENGTH = sizeof(memory) / sizeof(uint16_t);
    int i = 0;
    int ID = 0;
    uint16_t head = memory[0];
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
        /*
        sprintf(fp, "%d | ", ID);
        switch(i)
        {
            case 0:
                sprintf(fp, "halt");
                break;
            case 1:

                

        }
        sprintf(fp, "\n");
        */
    }

    fclose(fp);
}