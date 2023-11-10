#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#define MAX_CHAR_TYPE_COMBINATIONS 4

#define NUM_OF_LETTERS_IN_ALPHABET 26
#define	UPPERCASE_OFFSET 0x41
#define	LOWERCASE_OFFSET 0x61
#define	NUMBERS_OFFSET 0x30
#define	SPECIAL_START_OFFSET_1 0x20
#define	SPECIAL_START_OFFSET_2 0x3a
#define	SPECIAL_START_OFFSET_3 0x5b
#define	SPECIAL_START_OFFSET_4 0x7b
#define	SPECIAL_END_OFFSET_1 0x27
#define	SPECIAL_END_OFFSET_2 0x40
#define	SPECIAL_END_OFFSET_3 0x60
#define	SPECIAL_END_OFFSET_4 0x7e

#define IS_NUMBER(x) (NUMBERS_OFFSET <= x) & (x < NUMBERS_OFFSET + 10)

void InitSpecialCharArr(char *array);
void FillSpecialCharArr(char *array, int *index, int start, int end);

/* 
 * Formats and stores Character combination into char as a bitmask.
 * Arguments:
 * 	- `combinations`: pointer to string that needs parsing
 * - `num_combinations`: the size of the string
 *   Returns:
 *   	An int revealing the chosen options
 *
 *   	Bit num | Option
 *   	------- | -------------
 *   	1	|  Uppercase 
 *   	2	|  Lowercase
 *   	3	|  Number
 *   	4	|  Special char	
 *
 *   	for example:
 *   	0b1000 means user wants an Uppercase password
 *   	or
 *	0b0101 means user wants both Lowercase and Special characters
 */
int ParseCharCombinations(char *combinations, int num_combinations);

/*
 * Generates a random string of a given type.
 * Arguments:
 * 	- `types`: a int to indicate the group of characters allowed in the string
 * 	see ParseCharCombinations() for a detailed explenation
 *  - `size`: the length in characters of the requested string.
 * Returns:
 * 	A string of length `size` with only characters of type `type`. Returns `NULL` if `malloc` fails.
*/

char *GeneratePass(int types, size_t size);

/*
 * Prints the allowed arguments for the program.
*/
void ShowArguments();

int main(int argc, char** argv) 
{
	int num_combinations = 0;
	num_combinations = strlen(argv[1]);
	if(num_combinations <= MAX_CHAR_TYPE_COMBINATIONS) // 4 or less char combinations requested by user
	{
		switch (argc) 
		{
			case 1:
				fprintf(stderr, "No arguments specified");
				ShowArguments();
				return 1; // No need to break.
			case 2:
				fprintf(stderr, "Missing one argument");
				ShowArguments();
				return 1;
			default:
				{
				int size = -1;
				if( IS_NUMBER(*argv[2]) )
				{
					size = atoi(argv[2]);

					int combinations = ParseCharCombinations(argv[1], num_combinations);
					char *pass = GeneratePass(combinations, size);
					if (pass != NULL) 
					{
						#ifdef WRITE_TO_FILE
						
						#endif
						printf("Generated password: %s\n", pass);
						free(pass);
					}
					return 0; // No need to break.
				}
				else
				{
					fprintf(stderr, "Invalid Number of characters\n");
					return 1;
				}

				}
		}
	}
	else
	{
		fprintf(stderr, "Too many combinations specified");
		ShowArguments();
	}
}

char *GeneratePass(int char_types, size_t size)
{
	printf("%d",char_types);
	char specialchar[25];
	char *pass = (char*)malloc(size);
	if(pass != NULL)
	{
		srand(time(NULL));

		// generate random number from 0 to 3
		// then left shift by that number
		// random number
		//
		// Doesn't quite work for all cases
		
		switch(char_types)
		{
			// randomly choose characters and fill array
			case 0b1000:
				for(int count = 0; count < size; count++)
					 pass[count] = rand()%NUM_OF_LETTERS_IN_ALPHABET + UPPERCASE_OFFSET;
				break;
			case 0b0100:
				for(int count = 0; count < size; count++)
					 pass[count] = rand()%NUM_OF_LETTERS_IN_ALPHABET + LOWERCASE_OFFSET;
				break;
			case 0b0010:
				for(int count = 0; count < size; count++)
					 pass[count] = rand()%10 + NUMBERS_OFFSET;
				break;
			case 0b0001:
				InitSpecialCharArr(specialchar);
				for(int count = 0; count < size; count++)
					pass[count] = specialchar[ rand()%25 ];
				break;
			default:
				fprintf(stderr,"\e[0;31mWrong argument\e[0m");
				ShowArguments();	
				return NULL;
		}
	}
	else
		fprintf(stderr, "%s", strerror(errno));
	return pass;
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

int ParseCharCombinations(char *arguments, int num_combinations)
{
	int combination = 0;
	for(int count = 0; count < num_combinations; count++)
	{
		switch (arguments[count])
		{
			case 'u':
				combination |= 0b1000;
				break;
			case 'l':
				combination |= 0b0100;
				break;
			case 'n':
				combination |= 0b0010;
				break;
			case 's':
				combination |= 0b0001;
				break;
		}
	}
	return combination;
}

void ShowArguments(void)
{
	fprintf(stderr, ", please specify \e[1mone\e[0m of the following:"
			"\n\033[34mu\e[0m for uppercase\n"
			"\033[34ml\e[0m lowercase\n\033[34mn\e[0m for numbers"
			"\n\033[34ms\e[0m for special characters\n"
			"Also requires the number of desired characters "
			"for the password as a second argument.\n");
}

// NOT IMPLEMENTED
int Savetofile(char* pass) {
	assert(0 && "Not Implemented");
	return 0;
}

// NOT IMPLEMENTED
int CPtoClipboard(char* pass) {
	assert(0 && "Not Implemented");
	return 0;
}
