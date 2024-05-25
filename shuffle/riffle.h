/*
 * Riffle header.
 *
 * Provides function prototypes for riffle source.
 */

#include <string.h>

#include "util.h"

void riffle_once(void *, int, int, void *);
void riffle(void *, int, int, int);

int cmp_int(void *, void *);
int cmp_str(void *, void *);
int cmp_list(void *, void *, int, int, int (*)(void *, void *));
int check_shuffle(void *, int, int, int (*)(void *, void *));

float quality(int *, int);
float average_quality(int, int, int);
