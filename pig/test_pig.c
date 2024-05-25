#include "test_pig.h"

/*
 *
 * Test program for examples given in specification.
 *
 */

int main()
{
	char *result;

	char word1[] = "happy";
	result = pig(word1);
	printf("%s => %s\n", word1, result);
	free(result);
	
	char word2[] = "duck";
	result = pig(word2);
	printf("%s => %s\n", word2, result);
	free(result);
	
	char word3[] = "glove";
	result = pig(word3);
	printf("%s => %s\n", word3, result);
	free(result);
	
	char word4[] = "evil";
	result = pig(word4);
	printf("%s => %s\n", word4, result);	
	free(result);

	char word5[] = "eight";
	result = pig(word5);
	printf("%s => %s\n", word5, result);
	free(result);
	
	char word6[] = "yowler";
	result = pig(word6);
	printf("%s => %s\n", word6, result);
	free(result);
	
	char word7[] = "crystal";
	result = pig(word7);
	printf("%s => %s\n", word7, result);
	free(result);

	return 0;
}
