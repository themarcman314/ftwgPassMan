#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <assert.h>

#define UPPERCASE_OFFSET 0x41			// Offset of uppercase 'a' in the ASCII table.
#define NUM_OF_LETTERS_IN_ALPHABET 26	// Number of letters in the international alphabet.
#define LOWERCASE_OFFSET 0x61			// Offset of lowercase 'a' in the ASCII table.
#define NUMBERS_OFFSET 0x30				// Offset of the character '0' in the ASCII table.
#define SPECIAL_OFFSET 0x20				// Offset of the character `SP` in the ASCII table.

/*
 * Generates a random string of a given type.
 * Arguments:
 * 	- `type`: a character to indicate the group of characters allowed in the string.
 *  - `size`: the length in characters of the requested string.
 * Returns:
 * 	A string of length `size` with only characters of type `type`. Returns `NULL` if `malloc` fails.
*/
char* GeneratePass(char type, size_t size);

/*
 * Prints the allowed arguments for the program.
*/
void ShowArguments();

int main(int argc, char** argv) {
	switch (argc) {
	case 1:
		fprintf(stderr, "No arguments specified");
		ShowArguments();
		return 1; // No need to break.
	case 2:
		fprintf(stderr, "Missing one argument");
		ShowArguments();
		return 1; // No need to break.
	default:
		char* pass = GeneratePass(*argv[1], atoi(argv[2]));
		if (pass != NULL) {
			printf("Generated password: %s\n", pass);
			free(pass);
		}
		return 0; // No need to break.
	}
}

char* GeneratePass(char char_type, size_t size) {
	char* pass = (char*)malloc(size);

	// The opposite condition could be checked in order to maximize performance since the most common case is pass != NULL.
	if (pass == NULL) {
		return NULL;
	}

	srand(time(NULL)); // This is ok for now but if multiple calls to `GeneratePass` are made it's better to move this line in the `main` function.

	// Uppercase characters - u
	// 0x41 - 0x5a
	// Lowercase characters - l
	// 0x61 - 0x7a
	// Numbers		- n
	// 0x30 - 0x39
	// Special characters	- s
	// 0x20 - 0x27 | 0x3A - 0x40 | 0x5B - 0x60 | 0x7B - 0x7E

	switch (char_type) {
		// Randomly choose characters and fill array.
	case 'u':
		for (int count = 0; count < size; count++)
			pass[count] = rand() % NUM_OF_LETTERS_IN_ALPHABET + UPPERCASE_OFFSET;
		break;
	case 'l':
		for (int count = 0; count < size; count++)
			pass[count] = rand() % NUM_OF_LETTERS_IN_ALPHABET + LOWERCASE_OFFSET;
		break;
	case 'n':
		for (int count = 0; count < size; count++)
			pass[count] = rand() % 10 + NUMBERS_OFFSET;
		break;
	case 's': // NOT IMPLEMENTED
		for (int count = 0; count < size; count++)
			assert(0 && "not implemented");
		break;
	default:
		fprintf(stderr, "\e[0;31mWrong argument\e[0m");
		ShowArguments();
		return NULL;
	}

	return pass;
}

void ShowArguments() {
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
