#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "../includes/config.h"
#include "../includes/hosts.h"
#include "../includes/dnsfw.h"
#include "../includes/debug.h"


int LoadConfig(void);
host *headhost = NULL;
//static char *hostname(char *newline);
//static int *ports();



int LoadConfig(void)
{
	char *line = NULL;
	int linecount = 0;
	int version = 0;
	unsigned short int waitHost = TRUE;
	size_t len = 0;
	__ssize_t read;
	FILE *file = fopen(CONF_FILE, "r");
	//char name[DNS_SIZE + 1];
	//char portlist[255];
	//char pl[6];
	//unsigned short portArray[MAX_PORTS + 1]; // 0, 65,535
	//host Hosts[MAX_DNS_ENTRIES];
	headhost = malloc(sizeof(host));

	if (headhost == NULL)
	{
		// error
	}

	if (file == NULL)
	{
		printf("Unable to read from %s\n", CONF_FILE);
		return FAILED;
	}


	while ((read = getline(&line, &len, file)) != -1)
	{
		waitHost = TRUE;
		linecount++; // for error reporting purposes, always increase this.

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
				printf("bdnsdw.conf:%d -> duplicate version tag.\n", linecount);
				exit(0);
			}

			if (!isdigit(line[3]))
			{
				// Our version tag is not a numerical value, single digit in this case.
				printf("bdnsdw.conf:%d -> version %c is not numeric\n", linecount, line[3]);
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

		char *token = strtok(line, " "); // seperate by space
		host *curr;
		

		while (token != NULL)
		{
			// We are waiting for a hostname (ie: newline)
			if (waitHost)
			{
				// dtui
				if (strlen(token) > (sizeof(headhost->hostname) -1))
				{
					//printf("%s:%d > Host %s contains non-numeric port '%s'\n", CONF_FILE, linecount, curr->hostname, token);
					printf("%s:%d > Size of hostname exceeds allowed characters: %lu of max %d\n", CONF_FILE, linecount, strlen(token), DNS_SIZE);
					exit(1);
				}

				curr = addhost(headhost, token);
				printf("host add: %s\n", curr->hostname);
				waitHost = 0; // mark that we are waiting for a port now
			
				
			}  

			// We are not waiting for a hostname, assume (but verify) its a port list
			else
			{
				size_t s;
				
				s = strlen(token) - 1;

				if (token[s] == '\n')
					token[s] = '\0';

				// cycle through and confirm we are only a number, deal with bounds later.
				for (size_t k = 0; k <= s; k++)
				{
					//there is probably a cleaner way of doing all this... we will save it for when
					// i actually know wtf im doing in this language (aka v2)
					if (!isdigit(token[k]) && ((token[k] != '\0')))
					{
						printf("%s:%d > Host %s contains non-numeric port '%s'\n", CONF_FILE, linecount, curr->hostname, token);
						exit(1);
					}

					else if (token[k-1] == '\0')
						break; 
				}

				// valid port if we havn't died
				// the following if/else is a display rewrite only for adding port ALL
				if (token[1] == 0)
					printf("AddPort: %s:All\n", curr->hostname);
			
				else
					printf("AddPort: %s:%s\n", curr->hostname, token);

				if (addport(curr, token))
				{

				}

				else
				{
					
				}

			}
		
			token = strtok(NULL, " ");
		}
		// if we make it here, continue trying to process it.
		/*while (*line)
		{
			int hasdot = 0;
			char *myName;

			printf("%c", *line++);
		} */
	
	}



		//printf("%d: %s", linecount, line);
	
	return OK;

	
	
}
