#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../includes/version.h"

const char *getversion() //pointer return
{
	const size_t len1 = sizeof(VERSION_MAJOR);
	const size_t len2 = sizeof(VERSION_MINOR);
	const size_t len3 = sizeof(VERSION_PATCH);
	const size_t len4 = sizeof(VERSION_TAG);
	const size_t lentotal = len1 + len2 + len3 + len4;

	char *result = malloc(len1 + len2 + len3 + len4 + 4); // with . - and null term

	if (result == NULL)
	{
		printf("Error: Unable to allocate memory for version display");
		exit(1);
	}

	int j = snprintf(result, lentotal + 4, VERSION_FORMAT, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

	printf("result: %s - count: %d\n", result, j);

	return result;
	//ch
	//return sprintf("%d.%d", VERSION_MAJOR, VERSION_MINOR);
}