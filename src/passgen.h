#ifndef PASSGEN_H
#define PASSGEN_H
#include <stdio.h>

/*
 * Generates a random string of one or more character types.
 * Arguments:
 * 	- `types`: a int to indicate the group of characters allowed in the string
 * 	this int is 0b0100 for lower case or 0b0011 for numbers and special characters
 * 	see ParseCharCombinations() for a detailed explenation
 *  - `size`: the length in characters of the requested string.
 * Returns:
 * 	A string of length `size` with only characters of type `type`. Returns `NULL` if `malloc` fails.
*/
char *GeneratePass(int types, size_t num_char_types, size_t size);

#endif
