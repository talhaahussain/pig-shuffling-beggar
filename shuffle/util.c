/*
 * Utility source.
 *
 * Provides several functions for convenience.
 */

#include "util.h"

/*
 * Allocate some memory safely.
 *
 * If memory could not be allocated, then errno is used to indicate the kind of
 * error that occurred (see man malloc).
 *
 * Arguments:
 * 	size: number of bytes to allocate.
 *
 * Returns:
 * 	A pointer to the allocated memory.
 */
void *safe_malloc(unsigned int size)
{
	/* Allocate some memory. */
	void *ptr = malloc(size);

	/* Check if malloc failed. */
	if (ptr == NULL)
	{
		fprintf(stderr, "could not allocate memory\n");
		exit(errno);
	}
	else
	{
		return ptr;
	}
}

/*
 * Print a list of integers.
 *
 * The format of the list is [x, y, ..., z]. A newline character is printed at
 * the end of the list.
 *
 * Arguments:
 * 	list: the list of integers to print.
 * 	len: the length of the list.
 */
void print_int_list(int *list, unsigned int len)
{
	/* Print opening bracket. */
	printf("[");

	/* Loop up to penultimate element. */
	int i;
	for (i = 0; i < len - 1; i++)
	{
		printf("%d, ", list[i]);
	}

	/* Print last element with closing bracket. */
	printf("%d]\n", list[i]);
}

/*
 * Print a list of strings.
 *
 * The format of the list is [x, y, ..., z]. A newline character is printed at
 * the end of the list.
 *
 * Arguments:
 * 	list: the list of strings to print.
 * 	len: the length of the list.
 */
void print_str_list(char **list, unsigned int len)
{
	/* Print opening bracket. */
	printf("[");

	/* Loop up to penultimate element. */
	int i;
	for (i = 0; i < len - 1; i++)
	{
		printf("%s, ", list[i]);
	}

	/* Print last element with closing bracket. */
	printf("%s]\n", list[i]);
}

/*
 * Randomly generate a double precision number between 0 and 1.
 *
 * Returns:
 * 	A double precision number between 0 and 1.
 */
double rng()
{
	/* Calculate random number. */
	double r = (double) rand() / (float) RAND_MAX;
	return r;
}
