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
#include <unistd.h>
#include "iptables.h"
#include "config.h"
#include "dnsfw.h"
#include "debug.h"
#include "version.h"

int main(int argc, char *argv[])
{
	host *headhost = NULL; 
	headhost = malloc(sizeof(host));
//	to_log(DEBUG_DEBUG, "starting up...");

	printf("dnsfw v%s starting...\n", getversion());

	// we need to run as root
	if (getuid() > 0)
	{
		printf("error: please run as root.\n");
		//exit(1);
	}

	// check command line arguments
	if (argc > 1)
	{
		// if process_cli_args returns 0 it means we should exit/
		if (!process_cli_args(argc, argv))
			exit(1);
	}
	printf("logging to %s\nparsing %s...\n", CONF_LOG, CONF_FILE);
	LoadConfig(headhost);

	printf("Resolving hosts...\n");

	while (1)
	{
		run_dns_updates(headhost);

		sleep(30);
	}




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


void background_agent(void)
{

}

void run_dns_updates(host *head)
{
	host *cycle = NULL;
	cycle = head;

	while (cycle != NULL)
	{
		char *ip = resolve(cycle->hostname);
		int remove = FALSE;

		if (ip == NULL)
		{
			printf("%s does not resolve, is ipv6, or resolves more than once, skipping.\n", cycle->hostname);
			cycle = cycle->next;
			continue;
		}

		// if new ip is same as current we also continue.
		else if (strcmp(ip, cycle->currentIp) == 0)
		{
			printf("same ip, skip! %s\n", cycle->hostname);
			cycle = cycle->next;
			continue;
		}

		// we need to update this entry
		else
		{
			// if ip is not 0 we do need to remove old entries
			if (strcmp(cycle->currentIp, "0") != 0)
			{
				printf("%s: remove flag set ip %s\n", cycle->hostname, cycle->currentIp);
				remove = TRUE; // just set the flag so we can do it when we cycle ports
			}

			// check if wildcard entry
			if (cycle->is_wildcard)
			{
				// if we are supposed to do a removal first, do it.
				if (remove)
					iptables_del(cycle->currentIp, 0);

				// send it to iptables and then copy ip to our object
				iptables_add(ip, 0);
				strncpy(cycle->currentIp, ip, sizeof(cycle->currentIp) -1);
				printf("%s [%s] wildip updated!\n", cycle->hostname, cycle->currentIp);

				// we MUST continue from here on our loop
				// as having ports as wildcard is undefined.
				continue;
			}

			// cycle through all our ports,
			for (int i = 0; i < MAX_PORTS; i++)
			{
				// if we hit a null we stop
				if (cycle->ports[i] == '\0')
					break;

				if (remove)
				{
					iptables_del(cycle->currentIp, cycle->ports[i]);
				}

				iptables_add(ip, cycle->ports[i]);
				// lu?
				printf("%s added %d\n", cycle->hostname, cycle->ports[i]);
			}

			strncpy(cycle->currentIp, ip, sizeof(cycle->currentIp) -1);

			

			printf("%s: cycle complete\n", cycle->hostname);
		}

		// lets make sure that we do the firewall updates if the ip's do not match

		printf("%s is %s [old is %s]\n", cycle->hostname, ip, cycle->currentIp);
		//iptables_add(ip, 22);
		cycle = cycle->next;
	}
}
