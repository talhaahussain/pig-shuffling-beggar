#include <errno.h>
#include <stdlib.h>
#include <stdio.h>

typedef enum {false, true} BOOL;

void *safe_malloc(unsigned int size);
