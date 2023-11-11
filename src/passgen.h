#ifndef PASSGEN_H
#define PASSGEN_H
#include <stdio.h>

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

#endif
