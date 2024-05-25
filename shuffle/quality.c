#include "riffle.h"

int main()
{
	int min_shuffles = 1;
	int max_shuffles = 15;
	int array_size = 50;
	int number_of_trials = 30;

	printf("N\tQuality\n");

	int i;
	for (i = min_shuffles; i <= max_shuffles; i++) {
		printf("%d\t%f\n", i, average_quality(array_size, i, number_of_trials));
	}

	return 0;
}
