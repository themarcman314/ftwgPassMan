#include <assert.h>
#include <stdio.h>
#include "config.h"
#include "ansi_colors.h"

int Savetofile(char* pass) 
{
       	FILE *f = fopen(PATH_TO_SAVE_PASSWORDS, "w");
	if(f == NULL)
	{
		fprintf(stderr, RED"Failed to open file\n"COLOR_RESET);
		return 1;
	}
	if (fprintf(f,"%s", pass) < 0)
	{
		fprintf(stderr, RED"Failed to write to file\n"COLOR_RESET);
		fclose(f);
		return 1;
	}
	fclose(f);
	return 0;
}

