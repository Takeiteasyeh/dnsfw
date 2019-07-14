#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/config.h"
#include "../includes/hosts.h"
#include "../includes/dnsfw.h"


int LoadConfig(void);
//static char *hostname(char *newline);
//static int *ports();

host Hosts[MAX_DNS_ENTRIES];

int LoadConfig(void)
{
	char *line = NULL;
	int version = 0;
	size_t len = 0;
	__ssize_t read;
	FILE *file = fopen(CONF_FILE, "r");
	char name[DNS_SIZE + 1];
	int portArray[MAX_PORTS];


	if (file == NULL)
	{
		printf("Unable to read from %s\n", CONF_FILE);
		return FAILED;
	}

	int i = 0;
	while ((read = getline(&line, &len, file)) != -1)
	{
		i++; // for error reporting purposes, always increase this.

		// skip all comments, empty lines
		if ((line[0] == '#') || (line[0] == '\n')) // comments (also 0x24 ? or \35 ?)
			continue;

		// [! = 0x21 or  \33 ] [V = 0x56 or \86 ]
		if ((line[0] == '!') && (line[1] == 'V') && line[2] == ':') // version checking
		{
			// version string
			if (version > 0)
			{
				// We already have a version tag so why are we here?
				printf("bdnsdw.conf:%d -> duplicate version tag.\n", i);
				exit(0);
			}

			if (!isdigit(line[3]))
			{
				// Our version tag is not a numerical value, single digit in this case.
				printf("bdnsdw.conf:%d -> version %c is not numeric\n", i, line[3]);
				exit(0);
			}
			// the version of our database is too old to continue in this way.
			if ((int)line[3] < CONF_VERSION)
			{
				printf("Config version [%d] is too old (expected %d). Please see UPGRADE.TXT", line[3], CONF_VERSION);
				exit(0);
			}

			version = (int)line[3];
			continue;
		} // end of version tag

		// if we make it here, continue trying to process it.
	//	char name[DNS_SIZE + 1];
	//	int portArray[MAX_PORTS];

	// verify we have dns.something 20 30 40
	printf("\n%d:%s\n", i, line);
		if (sscanf(line, "%s %d", name, portArray[MAX_PORTS]))
		{
			printf("hostname: %s\n", name);

			for (int j = 0; j < MAX_PORTS; j++)
			{
				printf("index: %d - port: %d\n", j, portArray[j]);
			}
			
			continue;

		}
	}



		printf("%d: %s", i, line);
	
	return OK;

	
	
}
