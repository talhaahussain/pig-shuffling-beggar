#include "riffle.h"

int main()
{
	int shuffles = 5;

	int ints[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
	int ints_len = 20;
	int ints_size = sizeof(int);

	printf("INTS TEST\n");
	printf("Original list:\n");
	print_int_list(ints, ints_len);

	riffle(ints, ints_len, ints_size, shuffles);

	printf("List shuffled %d times:\n", shuffles);
	print_int_list(ints, ints_len);
	
	printf("Result from checking list: %d\n", check_shuffle(ints, ints_len, ints_size, cmp_int));

	printf("\n");

	char *strings[] = {"alpha", "beta", "gamma", "delta", "epsilon", "zeta", "eta", "theta", "iota", "kappa", "lambda", "mu"};
	int strings_len = 12;
	int strings_size = sizeof(char *);

	printf("STRINGS TEST\n");
	printf("Original list:\n");
	print_str_list(strings, strings_len);

	riffle(strings, strings_len, strings_size, shuffles);

	printf("List shuffled %d times:\n", shuffles);
	print_str_list(strings, strings_len);

	printf("Result from checking list: %d\n", check_shuffle(strings, strings_len, strings_size, cmp_str));

	return 0;
}
