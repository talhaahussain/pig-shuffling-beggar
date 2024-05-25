/*
 * Riffle source.
 *
 * Provides several functions related to riffle shuffling.
 */

#include "riffle.h"

/*
 * Performs one riffle shuffle of a list.
 *
 * The list is updated - a new shuffled list is not returned, instead the list
 * itself is shuffled. A second list is required to use as a "workspace" as
 * shuffling in-place is difficult. memmove is used to move data between arrays
 * as they are void *, so cannot be indexed.
 *
 * Arguments:
 * 	L: the list to shuffle.
 * 	len: the length of the list.
 * 	size: the size of the items in the list.
 * 	work: a list to use as a workspace.
 */
void riffle_once(void *L, int len, int size, void *work)
{
	/* Offset variables are used to calculate where to memmove to/from. */
	void *L_offset, *work_offset;

	/* Counter variables are used to count through the list. */
	int c = 0;
	int left = 0;
	int right = (len / 2);

	/* Loop until all elements on both the left and the right have been
	 * placed in work. */
	while ((left < (len / 2)) || (right < len))
	{
		/* Randomly choose between the left and right. */
		if (0.5 < rng())
		{
			/* Move an element from the left. */
			if (left < (len / 2))
			{
				/* Calculate offsets. */
				L_offset = L + (left++ * size);
				work_offset = work + (c++ * size);

				/* Move data in L to work. */
				memmove(work_offset, L_offset, size);
			}
		} 
		else 
		{
			/* Move an element from the right. */
			if (right < len)
			{
				/* Calculate offsets. */
				L_offset = L + (right++ * size);
				work_offset = work + (c++ * size);

				/* Move data in L to work. */
				memmove(work_offset, L_offset, size);
			}
		}
	}

	/* Move all data from work back to L. */
	for (c = 0; c < len; c++)
	{
		/* Calculate offsets. */
		L_offset = L + (c * size);
		work_offset = work + (c * size);

		/* Move data in work back to L. */
		memmove(L_offset, work_offset, size);
	}
}

/*
 * Performs N riffle shuffles of a list.
 *
 * The list is updated - a new shuffled list is not returned, instead the list
 * itself is shuffled. A "workspace" list is created to use with riffle_once.
 *
 * Arguments:
 * 	L: the list to shuffle.
 * 	len: the length of the list.
 * 	size: the size of the times in the list.
 * 	N: the number of shuffles to perform.
 */
void riffle(void *L, int len, int size, int N)
{
	/* Create a new workspace array. */
	void *work = safe_malloc(len * size);

	/* Perform N riffle shuffles. */
	int i;
	for (i = 0; i < N; i++)
	{
		riffle_once(L, len, size, work);
	}

	/* Free the memory allocated to work. */
	free(work);
}

/*
 * Compare two integers.
 *
 * Arguments:
 * 	arg_1: a pointer to the first integer.
 * 	arg_2: a pointer to the second integer.
 *
 * Returns:
 * 	If arg_1 is equal to arg_2, 0.
 * 	If arg_1 is greater than arg_2, -1.
 * 	If arg_1 is less than arg_2, 1.
 */
int cmp_int(void *arg_1, void *arg_2)
{
	/* Cast the arguments to integer values that can be compared. */
	int int_1 = *(int *) arg_1;
	int int_2 = *(int *) arg_2;

	/* Arguments are equal. */
	if (int_1 == int_2)
	{
		return 0;
	}
	/* Argument 1 is greater. */
	else if (int_1 > int_2)
	{
		return -1;
	}
	/* Argument 1 is lesser. */
	else if (int_1 < int_2)
	{
		return 1;
	}
}

/*
 * Compare two strings.
 *
 * Arguments:
 * 	arg_1: a pointer to the first string.
 * 	arg_2: a pointer to the second strings.
 *
 * Returns:
 * 	If arg_1 is equal to arg_2, 0.
 * 	If arg_1 is greater than arg_2, -1.
 * 	If arg_1 is less than arg_2, 1.
 */
int cmp_str(void *arg_1, void *arg_2)
{
	/* Cast the arguments to string values that can be compared. */
	char *str_1 = arg_1;
	char *str_2 = arg_2;

	/* Get result from strcmp. */
	int c = strcmp(str_1, str_2);

	/* Arguments are equal. */
	if (c == 0)
	{
		return 0;
	}
	/* Argument 1 is greater. */
	else if (c > 0)
	{
		return -1;
	}
	/* Argument 1 is lesser. */
	else if (c < 0)
	{
		return 1;
	}
}

/*
 * Compare two lists.
 *
 * Checks if every element in list 1 is also in list 2.
 *
 * Arguments:
 * 	L1: list 1.
 * 	L2: list 2.
 * 	len: length of list 1.
 * 	size: size of elements in both lists.
 * 	cmp: a function to compare elements.
 *
 * Returns:
 * 	If all elements in list 1 are present in list 2, 1.
 * 	Otherwise, 0.
 */
int cmp_list(void *L1, void *L2, int len, int size, int (*cmp)(void *, void *))
{
	/* Counter variables are used to iterate through lists. */
	int i, j, r;

	/* Offsets variables are used to move through lists. */
	void *L1_offset, *L2_offset;

	/* For every element in L1... */
	for (i = 0; i < len; i++)
	{
		/* Calculate offset. */
		L1_offset = L1 + (i * size);

		/* For every element in L2... */
		for (j = 0; j < len; j++)
		{
			/* Calculate offset. */
			L2_offset = L2 + (j * size);

			/* Use comparison function to compare values at
			 * offsets. */
			r = (*cmp)(L1_offset, L2_offset);

			/* Element matches, exit. */
			if (r == 0)
			{
				break;
			}
		}

		/* If the end of L2 is reached and an element in L1 was not
		 * found, return 0. */
		if (j == len)
		{
			return 0;
		}
	}

	/* All elements in L1 are in L2, return 1. */
	return 1;
}

/*
 * Check the integrity of a shuffle.
 *
 * When shuffling, the should retain integrity - all elements in the original
 * list are also in the shuffled list (and vice versa). check_shuffle uses
 * cmp_list to ensure this property holds after a list is shuffled a few times.
 *
 * Arguments:
 * 	L: the list to shuffle and check.
 * 	len: the length of the list.
 *	size: the size of the elements in the list.
 *	cmp: a function to compare elements.
 *
 * Returns:
 * 	If a shuffle retains integrity, 1. Otherwise, 0.
 */
int check_shuffle(void *L, int len, int size, int (*cmp)(void *, void *))
{
	/* original is a copy of L. */
	void *original = safe_malloc(len * size);

	/* Offset variables are used to move through lists. */
	void *L_offset, *original_offset;

	/* Counter variables are used to iterate through a list. */
	int i, j;

	/* Save a copy of data from L into original. */
	for (i = 0; i < len; i++)
	{
		/* Calculate offsets. */
		L_offset = L + (i * size);
		original_offset = original + (i * size);

		/* Move data in L to original. */
		memmove(original_offset, L_offset, size);
	}

	/* Perform a riffle shuffle. */
	riffle(L, len, size, 5);

	/* Perform 2 checks: that all elements in L are in original, and that
	 * all elements in original are in L. */
	int r = cmp_list(original, L, len, size, cmp) && cmp_list(L, original, len, size, cmp);

	/* Free allocated memory. */
	free(original);

	/* Return result. */
	return r;
}

/*
 * Calculate the quality from a list of integers.
 *
 * Quality is calculated as the ratio of adjacent elements where the second
 * element is greater than the first compared to the total number of adjacent
 * elements.
 *
 * Arguments:
 * 	numbers: a list of numbers.
 * 	len: the length of the list.
 *
 * Returns:
 * 	A floating point value representing the quality.
 */
float quality(int *numbers, int len)
{
	int ratio = 0;
	int comparisons = len - 1;

	/* Loop through list of numbers. */
	int i;
	for (i = 0; i < comparisons; i++)
	{
		/* Get adjacent elements and increment ratio. */
		if (numbers[i] < numbers[i + 1])
		{
			ratio++;
		}
	}

	/* Return quality as ratio divided by total number of comparisons. */
	return (float) ratio / (float) (comparisons);
}

/*
 * Calculate the average quality over several trials.
 *
 * Arguments:
 * 	N: size of the array of integers.
 * 	shuffles: number of shuffles to perform.
 * 	trials: number of trials to average over.
 *
 * Returns:
 * 	A floating point value representing the average quality.
 */
float average_quality(int N, int shuffles, int trials)
{
	float results[trials], trial_quality, sum, average;

	/* numbers is used to store actual values to shuffle. */
	int numbers[N];

	int i, j;
	/* For every trial... */
	for (i = 0; i < trials; i++)
	{
		/* Populate the numbers array. */
		for (j = 0; j < N; j++)
		{
			numbers[j] = j;
		}

		/* Riffle numbers shuffles times. */
		riffle(numbers, N, sizeof(int), shuffles);

		/* Calculate the quality of this particular trial. */
		trial_quality = quality(numbers, N);

		/* Add quality to list. */
		results[i] = trial_quality;
	}

	/* Calculate and return average quality over all trials. */
	sum = 0;
	for (i = 0; i < trials; i++)
	{
		sum += results[i];
	}

	return sum / (float) trials;
}
