/*
 * Utility header.
 *
 * Provides function prototypes for utilities source.
 */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

void *safe_malloc(unsigned int);

void print_int_list(int *, unsigned int);
void print_str_list(char **, unsigned int);

double rng();
