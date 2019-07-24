#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "../includes/version.h"

const char *getversion() //pointer return
{
	const size_t lentotal = sizeof(VERSION_MAJOR) + sizeof(VERSION_MINOR) + sizeof(VERSION_PATCH) + sizeof(VERSION_TAG) + 4;

	char *result = malloc(lentotal); // with . - and null term

	if (result == NULL)
	{
		printf("Error: Unable to allocate memory for version display");
		exit(1);
	}

	int j = snprintf(result, lentotal, VERSION_FORMAT, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

	assert(j <= lentotal);
	
	return result;
}