#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include "debug.h"
#include "config.h"

void debug(int level, char *file, char *sub, int line, char *message)
{

}

void to_log(int level, char *message)
{
	if ((level & DEBUG_LEVEL) == 0)
	{
		return;
	}

	FILE *fptr;
	int count;

	// add newline
	char *msgnl;
	msgnl = malloc(sizeof(message) + 2);
	strcpy(msgnl, message);
	strcat(msgnl, "\n");
	
	fptr = fopen(CONF_LOG, "a");

	if (fptr == NULL)
	{
		printf("Unable to write to log file: %s\n", CONF_LOG);
	}

	else
	{
		count = fwrite(msgnl, 1, strlen(msgnl), fptr);
		printf("written %d of %lu\n", (int)count, strlen(msgnl) - 1);
		fclose(fptr);
	}

	printf("%s", msgnl);

}

void sprintf_log(int level, char *format, ...)
{
	va_list parg;
	char *buffer[1024];

	if ((level & DEBUG_LEVEL) == 0)
	{
		return;
	}

	FILE *fptr;
	int count;

	va_start(parg, format);
	int buffsize;
	// add newline
	//char *msgnl;
	//msgnl = malloc(strlen(p_sprintf) + 2);
	buffsize = vsnprintf(buffer, sizeof(buffer), format, parg);

	while (buffsize == sizeof(buffer))
	{
		realloc(buffer, (sizeof(buffer) + 1024));
		buffsize = vsnprintf(buffer, sizeof(buffer), format, parg);

		// ensure room for our line feed
		if ((sizeof(buffer) - buffsize) < 1)
			realloc(buffer, sizeof(buffer) + 1);
	}

	//strcpy(msgnl, p_sprintf);
	strcat(buffer, "\n");
	
	fptr = fopen(CONF_LOG, "a");

	if (fptr == NULL)
	{
		printf("Unable to write to log file: %s\n", CONF_LOG);
	}

	else
	{
		count = fwrite(buffer, 1, strlen(buffer), fptr);
	//	printf("written %d of %lu\n", (int)count, strlen(msgnl) - 1);
		fclose(fptr);
	}

	//printf("%s", msgnl);
}

char *levelname(int level)
{
	char *type = NULL;

	switch (level)
	{
		case DEBUG_NONE:
			type = "None";
			break;

		case DEBUG_FATAL:
			type = "Fatal";
			break;

		case DEBUG_ERROR:
			type = "Error";
			break;

		case DEBUG_WARNING:
			type = "Warn";
			break;

		case DEBUG_INFO:
			type = "Info";
			break;

		case DEBUG_DEBUG:
			type = "Debug";
			break;

		case DEBUG_TRACE:
			type = "None";
			break;

		default:
			type = "undefined";
			break;
	}

	return type;
}