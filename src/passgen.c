#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include "passgen.h"
#include "main.h"

void InitSpecialCharArr(char *array);
void FillSpecialCharArr(char *array, int *index, int start, int end);
void FillCharTypesArray(int user_types, int * char_type_selection);


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
