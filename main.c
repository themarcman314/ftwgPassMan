#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

char *GeneratePass(char type, size_t size);
void show_arguments(void);

int main(int argc, char **argv)
{
	if(argc == 1)
	{
		fprintf(stderr, "No arguments specified");
		show_arguments();
		return 1;
	}
	if(argc == 2)
	{
		fprintf(stderr, "Missing one argument");
		show_arguments();
		return 1;
	}
	char *pass = GeneratePass(*argv[1], atoi(argv[2]));
	if(pass != NULL)
	{
		printf("Generated password: %s\n", pass);
		free(pass);
	}
	return 0;
}

char *GeneratePass(char char_type, size_t size)
{
	const int NUM_OF_LETTERS_IN_ALPHABET = 26;
	const int UPPERCASE_OFFSET = 0x41;
	const int LOWERCASE_OFFSET = 0x61;
	const int NUMBERS_OFFSET = 0x30;
	const int SPECIAL_OFFSET = 0x20;

	char *pass = malloc(size);
	if(pass == NULL)
		goto error;
		
	srand(time(NULL));

	// Uppercase characters - u
	// 0x41 - 0x5a
	// Lowercase characters - l
	// 0x61 - 0x7a
	// Numbers		- n
	// 0x30 - 0x39
	// Special characters	- s
	// 0x20 - 0x27 | 0x3A - 0x40 | 0x5B - 0x60 | 0x7B - 0x7E

	switch(char_type)
	{
		// randomly choose characters and fill array
		case 'u':
			for(int count = 0; count < size; count++)
				 pass[count] = rand()%NUM_OF_LETTERS_IN_ALPHABET + UPPERCASE_OFFSET;
			break;
		case 'l':
			for(int count = 0; count < size; count++)
				 pass[count] = rand()%NUM_OF_LETTERS_IN_ALPHABET + LOWERCASE_OFFSET;
			break;
		case 'n':
			for(int count = 0; count < size; count++)
				 pass[count] = rand()%10 + NUMBERS_OFFSET;
			break;
		case 's':
			for(int count = 0; count < size; count++)
				assert(0 && "not implemented");
			break;
		default:
			fprintf(stderr,"\e[0;31mWrong argument\e[0m");
			show_arguments();	
			return NULL;
	}
		
	error:		
		/*if(pass != NULL)
		{
			free(pass);
		}
	*/

	return pass;
}

void show_arguments(void)
{
			fprintf(stderr, ", please specify \e[1mone\e[0m of the following:"
					"\n\033[34mu\e[0m for uppercase\n"
					"\033[34ml\e[0m lowercase\n\033[34mn\e[0m for numbers"
					"\n\033[34ms\e[0m for special characters\n"
					"Also requires the number of desired characters "
					"for the password as a second argument.\n");
}
