/*
 * Bacon Dynamic Dns FireWall updater
 * This program comes with absolutely NO WARRANTY
 *
 * Raymond Lynk - rlynk@bacon.place
 * 
 * File: dnsfw.c
 * Info: main run file for the bdnsfw service 
 *
 */

#include <stdio.h>
#include <stdlib.h> // malloc, calloc, realloc, free
#include "../includes/config.h"
#include "../includes/dnsfw.h"
#include "../includes/hosts.h"
extern const char *getversion(void);
extern int LoadConfig(void);

int main(int argc, char *argv[])
{
	printf("dnsfw v%s\n", getversion());

	// check command line arguments
	if (argc > 1)
	{
		// if process_cli_args returns 0 it means we should exit/
		if (!process_cli_args(&argc, &argv))
			exit(1);
	}
	printf("reading config...");
	LoadConfig();

	//printf("dnsfw: v%s\n", FULL_VERSION);	
}

/**
 * If we return 0, the process will end, return 1 to continue
 */
int process_cli_args(int argc, char argv[])
{
	int retcode = 0; // by default, any cli arguments are considered fatal to the application

	switch (argv[2])
	{
		case '-h':
		case '--help':
			if (argc > 2)
				process_cli_help(argv[3]);
			else
				process_cli_help();
		break; // exit code 0

		case '-g':
		case '-genconf':
			process_cli_genconf();
			break;

		case '-l':
		case '--list':
			// not yet  available;
			printf("not yet implemented");
			break;

		case '-a':
		case '--add':
			printf("not yet implemented");
			break;

		case '-d':
		case '--delete':
			printf("not yet implemented");
			break;
			
		default:
			printf("Unknown arguments [%s] .. ignoring...\n", argv[2]);
			retcode = 1;
			break;
	}

	return retcode;


	}
}



