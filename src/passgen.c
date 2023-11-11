#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "passgen.h"
#include "main.h"

/*
 * Initialises an array with special characters by calling FillSpecialCharArr
 * 	- `array`: the char array to be filled
 */
static void InitSpecialCharArr(char *array);

/*
 * Fills an array with ASCII characters from and including `start` to `end`
 * 	- `array`: the char array to be filled
 * 	- `index`: the address to an integer index so that the position at which we are filling the array is known
 */
static void FillSpecialCharArr(char *array, int *index, int start, int end);


/*
 * Fills an array with the character types requested by user
 * rand() should later be used to randomly select the type for the next password character
 * 	- `user_types`: integer with user requested types 
 * 	each type is represented by a bit (see ParseCharCombinations() in main.c)
 *	- `char_type_selection`: integer array where every selected character type is represented by an integer
 */
static void FillCharTypesArray(int user_types, int *char_type_selection);


char *GeneratePass(int user_types, size_t num_char_types, size_t size)
{
	char specialchar[25];
	char *pass = (char*)malloc(size);
	if(pass != NULL)
	{

		InitSpecialCharArr(specialchar);
		srand(time(NULL));
		
		int types[num_char_types]; // Here we will store information from user selected types
		FillCharTypesArray(user_types, types);
		
		int randomtype = 0;
		for(int count = 0; count < size; count++)
		{
			randomtype = types[rand()%num_char_types]; // Select a character type from user input
			switch(randomtype)
			{
				// randomly choose characters and fill array
				case 0b1000:
					pass[count] = rand()%NUM_OF_LETTERS_IN_ALPHABET + UPPERCASE_OFFSET;
					break;
				case 0b0100:
					pass[count] = rand()%NUM_OF_LETTERS_IN_ALPHABET + LOWERCASE_OFFSET;
					break;
				case 0b0010:
					pass[count] = rand()%10 + NUMBERS_OFFSET;
					break;
				case 0b0001:
					pass[count] = specialchar[ rand()%25 ];
					break;
				default:
					fprintf(stderr,"\e[0;31mWrong argument\e[0m");
					ShowArguments();	
					return NULL;
			}
		}
	}
	else
		fprintf(stderr, "%s", strerror(errno));
	return pass;
}

void FillCharTypesArray(int user_types, int * char_type_selection)		
{
	int type = 0;
	int index = 0;
	for(int count = 0; count < MAX_CHAR_TYPE_COMBINATIONS; count++)
	{
		type = 1 << count;
		if(user_types & type)
		{
			char_type_selection[index] = type;	
			index++;
		}
	}
}


void InitSpecialCharArr(char *array)
{
	// 0x20 - 0x27 | 0x3A - 0x40 | 0x5B - 0x60 | 0x7B - 0x7E
	int index = 0;
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_1, SPECIAL_END_OFFSET_1);
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_2, SPECIAL_END_OFFSET_2);
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_3, SPECIAL_END_OFFSET_3);
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_4, SPECIAL_END_OFFSET_4);
}

void FillSpecialCharArr(char *array, int *index, int start, int end)
{
	for(int count = start; count <= end; count++)
	{
		array[*index] = count;	
		(*index)++;
	}
}
