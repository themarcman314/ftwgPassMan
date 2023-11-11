#include <stdio.h>

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

/*
 * Generates a random string of a given type.
 * Arguments:
 * 	- `types`: a int to indicate the group of characters allowed in the string
 * 	see ParseCharCombinations() for a detailed explenation
 *  - `size`: the length in characters of the requested string.
 * Returns:
 * 	A string of length `size` with only characters of type `type`. Returns `NULL` if `malloc` fails.
*/
char *GeneratePass(int types, size_t num_char_types, size_t size);

