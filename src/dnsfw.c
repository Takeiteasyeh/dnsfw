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
#include <string.h>
#include <stdlib.h> // malloc, calloc, realloc, free
#include "../includes/config.h"
#include "../includes/dnsfw.h"
#include "../includes/hosts.h"
#include "../includes/debug.h"

extern const char *getversion(void);
extern int LoadConfig(void);

int main(int argc, char *argv[])
{
	to_log(DEBUG_DEBUG, "starting up...");

	printf("dnsfw v%s (debug type: %s)\n", getversion(), levelname(DEBUG_DEBUG));

	// check command line arguments
	if (argc > 1)
	{
		// if process_cli_args returns 0 it means we should exit/
		if (!process_cli_args(argc, argv))
			exit(1);
	}
	printf("reading config...");
	LoadConfig();

	//printf("dnsfw: v%s\n", FULL_VERSION);	
}

/**
 * If we return 0, the process will end, return 1 to continue
 */
int process_cli_args(int argc, char *argv[])
{
	int retcode = 0; // by default, any cli arguments are considered fatal to the application
	
	//printf("arvg is %s\n", argv[1]);
	//return 0;

	if ((strncmp(argv[1], "-h", 3) == 0) || (strncmp(argv[1], "--help", 7) == 0))
	{
		if (argc >2 )
			process_cli_help_param(argv[2]);
		
		else
			process_cli_help();
	}

	else if ((strncmp(argv[1], "-g", 3) == 0) || (strncmp(argv[1], "--genconf", 10) == 0))
	{
		printf("genconf\n");
	} 

	else if ((strncmp(argv[1], "-l", 3) == 0) || (strncmp(argv[1], "--list", 7) == 0))
	{
		printf("test block\n");
	} 

	else if ((strncmp(argv[1], "-a", 3) == 0) || (strncmp(argv[1], "--add", 6) == 0))
	{
		printf("test block\n");
	} 
	
	else if ((strncmp(argv[1], "-r", 3) == 0) || (strncmp(argv[1], "--remove", 9) == 0))
	{
		printf("test block\n");
	} 




	return retcode;
}

void process_cli_help(void)
{
	printf("# bdnsfw: help\n");
	printf("# description: Resolve dynamic dns for automatic firewall updates\n");
	printf("#\n");
	printf("# -h | --help          This screen.\n");
	printf("# -g | --genconf       Generate the first-run ip config.\n");
	printf("# -l | --list          List rDNS entries -- not implemented.\n");
	printf("# -a | --add           Adds entries to the rDNS database.\n");
	printf("# -r | --remove        Remove entries from the rDNS database.\n");
	printf("# end of help index.\n");
}

void process_cli_help_param(char *topic)
{
	if (strncmp(topic, "genconf", 8) == 0)
	{
		printf("# bdnsfw: help genconf\n");
		printf("# description: Generate the initial configuration file\n");
		printf("#\n");
		printf("# -g | --genconf      You will be prompted.\n");
	}

	else if (strncmp(topic, "list", 6) == 0)
	{
		printf("# bdnsfw: help list\n");
		printf("# description: Lists all rDNS hosts we monitor.\n");
		printf("#\n");
		printf("# -l | --list          Takes no parameters.\n");
	}

	else if (strncmp(topic, "add", 6) == 0)
	{
		printf("# bdnsfw: help add\n");
		printf("# description: Add to the rDNS hosts.\n");
		printf("#\n");
		printf("# -a | --add          You will be prompted.n");
	}

	else if (strncmp(topic, "remove", 6) == 0)
	{
		printf("# bdnsfw: help remove\n");
		printf("# description: Remove from the rDNS hosts.\n");
		printf("#\n");
		printf("# -r | --remove [host]      Removes the given host\n");
	}

	else
	{
		printf("# bdnsfw: unknown help topic.\n");
	}
}



