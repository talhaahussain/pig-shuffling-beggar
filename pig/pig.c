#include "pig.h"


/*
 * Translates a string to its Pig latin equivalent.
 *
 * Arguments:
 * 	A pointer to a char of a char array (string), the word to be translated.
 *
 * Returns:
 * 	A pointer to a char of a char array (string), the translated result.
 *
 */
char *pig(char *word)
{
	char *result;
	if (word[0] == 'a' || word[0] == 'e' || word[0] == 'i' || word[0] == 'o' || word[0] == 'u' || word[0] =='A' || word[0] == 'E' || word[0] == 'I' || word[0] == 'O' || word[0] == 'U') /* Check for vowels, upper and lower case */
	{
		int n = strlen(word) + 4; /* Space for suffix */
		if (!(result = (char *)malloc(n*sizeof(char)))) /* Safe malloc */
		{
			printf("Out of memory!\n");
			exit(1);
		}
		strcpy(result, word);
		strcat(result, "way");
	}
	else 
	{
		int n = strlen(word) + 3; /* Space for char transpose and suffix */
		if (!(result = (char *)malloc(n*sizeof(char)))) /* Safe malloc */
		{
			printf("Out of memory!\n");
			exit(1);
		}

		int i;
		char consonants[strlen(word)+1];
		char *word_copy = word;
		for (i = 0; i < strlen(word_copy); i++)
		{
			if (word_copy[i] == 'a' || word_copy[i] == 'e' || word_copy[i] == 'i' || word_copy[i] == 'o' || word_copy[i] == 'u' || word_copy[i] == 'A' || word_copy[i] == 'E' || word_copy[i] == 'I' || word_copy[i] == 'O' || word_copy[i] == 'U' || (word_copy[i] == 'y' && i != 0) || (word_copy[i] == 'Y' && i != 0)) /* Only accept 'y' as vowel if it isn't the first character of the word */
			{
				break;
			}
			else
			{
				consonants[i] = word[i];
				consonants[i+1] = '\0'; /* Move the null terminator forward */
			}

		}
		strcpy(result, word + i);
		strcat(result, consonants);
		strcat(result, "ay");
	}
	return result;
}
