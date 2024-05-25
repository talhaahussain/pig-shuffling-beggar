/* Compiler directives. */

#include "util.h"

/* Function definitions. */

/* Safely allocate some memory. */
void *safe_malloc(unsigned int size) {
	/* Attempt to allocate some memory. */
	void *ptr = malloc(size);

	/* Check if allocation was successful. */
	if (ptr == NULL) {
		/* Allocation failed, report error to user. */
		fprintf(stderr, "Fatal! Could not allocate memory.\n");
		exit(ENOMEM);
	}
	else {
		/* Allocation successful, return pointer. */
		return ptr;
	}
}
