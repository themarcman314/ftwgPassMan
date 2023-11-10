#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#include <assert.h>

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

void InitSpecialCharArr(char* array);
void FillSpecialCharArr(char* array, int* index, int start, int end);

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

/*
 * Saves a password in a text file.
 * Assumes the file does not exist or is empty or it can be overwritten.
 * Assumes the password is valid does not contain any spaces or newlines.
 * Arguments:
 *  - `pass`: a string containing the password to save.
 *  - `filename`: a string containing the name of the file.
 * Returns:
 * 	An integer thast indicates if the operation was succesfull:
 * 	 - `0`: operation succesfull.
 *   - `1` : operation failed.
*/
int Savetofile(char* pass, char* filename);

int main(int argc, char** argv) {
	switch (argc) {

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
		if (IS_NUMBER(*argv[2])) {
			size = atoi(argv[2]);
			char* pass = GeneratePass(*argv[1], size);
			if (pass != NULL) {
				printf("Generated password: %s\n", pass);
				free(pass);
			}
			return 0; // No need to break.
		} else {
			fprintf(stderr, "Invalid Number of characters\n");
			return 1;
		}

	}
	}
}

char* GeneratePass(char char_type, size_t size) {

	char specialchar[25];
	char* pass = (char*)malloc(size);
	if (pass != NULL) {
		srand(time(NULL));

		switch (char_type) {
			// randomly choose characters and fill array
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
		case 's':
			InitSpecialCharArr(specialchar);
			for (int count = 0; count < size; count++)
				pass[count] = specialchar[rand() % sizeof(specialchar)];
			break;
		default:
			fprintf(stderr, "\e[0;31mWrong argument\e[0m");
			ShowArguments();
			return NULL;
		}
	} else
		fprintf(stderr, "%s", strerror(errno));
	return pass;
}

void InitSpecialCharArr(char* array) {
	// 0x20 - 0x27 | 0x3A - 0x40 | 0x5B - 0x60 | 0x7B - 0x7E
	int index = 0;
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_1, SPECIAL_END_OFFSET_1);
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_2, SPECIAL_END_OFFSET_2);
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_3, SPECIAL_END_OFFSET_3);
	FillSpecialCharArr(array, &index, SPECIAL_START_OFFSET_4, SPECIAL_END_OFFSET_4);
}

void FillSpecialCharArr(char* array, int* index, int start, int end) {
	for (int count = start; count <= end; count++) {
		array[*index] = count;
		(*index)++;
	}
}

void ShowArguments(void) {
	fprintf(stderr, ", please specify \e[1mone\e[0m of the following:"
		"\n\033[34mu\e[0m for uppercase\n"
		"\033[34ml\e[0m lowercase\n\033[34mn\e[0m for numbers"
		"\n\033[34ms\e[0m for special characters\n"
		"Also requires the number of desired characters "
		"for the password as a second argument.\n");
}

// NOT IMPLEMENTED
int Savetofile(char* pass, char* filename) {
	FILE* file = fopen(filename, "w");

	if (file != NULL) {
		fprintf(file, "%s", pass); // As long as the password DOES NOT contain spaces or newlines
		fclose(file);
		return 0;
	} else {
		return 1;
	}
}

// NOT IMPLEMENTED
int CPtoClipboard(char* pass) {
	assert(0 && "Not Implemented");
	return 0;
}
