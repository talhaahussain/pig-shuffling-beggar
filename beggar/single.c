#include "beggar.h"

int get_number_of_players(char *string)
{
	char *end_ptr;
	errno = 0;


	int number_of_players = strtol(string, &end_ptr, 10);

	if (errno != 0)
	{
		perror("strtol");
		exit(EXIT_FAILURE);
	}

	if (end_ptr == string)
	{
		fprintf(stderr, "no digits found\n");
		exit(EXIT_FAILURE);
	}

	if (number_of_players < 0) {
		fprintf(stderr, "invalid argument supplied (number of players was negative)\n");
		exit(EINVAL);
	}

	return number_of_players;
}

int main(int argc, char *argv[])
{
	int number_of_players;

	if (!(argc == 2))
	{
		fprintf(stderr, "incorrect number of arguments supplied\n");
		exit(EINVAL);
	}
	else
	{
		number_of_players = get_number_of_players(argv[1]);
	}
	printf("%d\n", number_of_players);

	return 0;

}
