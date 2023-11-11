#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <assert.h>

#include "main.h"
#include "passgen.h"
#include "ansi_colors.h"


#define IS_NUMBER(x) (NUMBERS_OFFSET <= x) & (x < NUMBERS_OFFSET + 10)

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


int main(int argc, char** argv) 
{
	int num_char_combinations = 0;
	int pass_size = -1;
		switch (argc) 
		{
			case 1:
				fprintf(stderr, RED"No arguments specified"COLOR_RESET);
				ShowArguments();
				return 1; // No need to break.
			case 2:
				fprintf(stderr, RED"Missing one argument"COLOR_RESET);
				ShowArguments();
				return 1;
			default:
				{
					num_char_combinations = strlen(argv[1]);
					if(num_char_combinations <= MAX_CHAR_TYPE_COMBINATIONS) // 4 or less char combinations requested by user
					{
						if( IS_NUMBER(*argv[2]) )
						{
							pass_size = atoi(argv[2]);

							int combinations = ParseCharCombinations(argv[1], num_char_combinations);
							char *pass = GeneratePass(combinations, num_char_combinations, pass_size);
							if (pass != NULL) 
							{
								#ifdef WRITE_TO_FILE
								
								#endif
								printf("Generated password:\n%s\n", pass);
								free(pass);
							}
							return 0; // No need to break.
						}
						else
						{
							fprintf(stderr, "Invalid password size\n");
							ShowArguments();
							return 1;
						}
					}
					else
					{
						fprintf(stderr, "Too many character combinations specified");
						ShowArguments();
					}
				}
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
	fprintf(stderr, ", please specify"BOLD" up to four "COLOR_RESET"of the following:"
			"\n"GRN"u"COLOR_RESET" for uppercase\n"
			GRN"l"COLOR_RESET" lowercase\n"GRN"n"COLOR_RESET" for numbers"
			"\n"GRN"s"COLOR_RESET" for special characters\n"
			"Also requires the number of desired characters "
			"for the password as a second argument.\n");
}
