#include "piglatin.h"

int main() 
{
	char input[500];
	while(true) /* Program loop */
	{
		/* Creating space separation between user inputs */
		printf("\n");
		printf("\n");
		printf("Type something...\n");
		fgets(input, sizeof(input), stdin);
		if (!strcmp(input, "\n")) /* If an empty line is entered, break out of program loop */
		{
			printf("Input is empty: %s\n", input);
			break;
		}
		input[strlen(input)-1] = '\0'; /* Remove null terminator from string */
		pig_latin(input);		
	}
	return 0;
}

/*
 * Breaks a string into tokens (by whitespace separation), executes 'pig' method on them and prints the resultant.
 *
 * Arguments:
 * 	input_str: A string to be broken down and translated.
 *
 * Returns:
 * 	none
 *
 */
void pig_latin(char *input_str) {
	char *token, *str, *to_free;
	to_free = str = strdup(input_str);

	char *pig_str;
	while ((token = strsep(&str, " "))) {
		pig_str = pig(token);
		printf("%s ", pig_str);
		free(pig_str);
	}
	free(to_free);
}
