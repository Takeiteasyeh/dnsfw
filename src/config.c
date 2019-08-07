/*                                                       )
          ,%,                                     ) _(___[]_
          %%%,&&&, dnsfw.bacon.place   ,%%,      (;`       /\
          %Y/%&&&&  rlynk@bacon.place  %%%%   ___/_____)__/ _\__     ,%%,
        ^^^||^&\Y&^^^^^^^^^^^^^^^^^^^^^%Y/%^^/ (_()   (  | /____/\^^^%%%%^^
          `    || _,..=xxxxxxxxxxxx,    ||   |(' |LI (.)I| | LI ||   %\Y%
         -=      /L_Y.-"""""""""`,-n-. `    @'---|__||___|_|____||_   ||
        ___-=___.--'[========]|L]J: []\ __________@//@___________) )______
       -= _ _ _ |/ _ ''_ " " ||[ -_ 4 |  _  _  _  _  _  _  _  _  _  _  _
                '-(_)-(_)----'v'-(_)--'
       jgs-----------------------------------------------------------------
*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "config.h"
//#include "hosts.h"
#include "dnsfw.h"
#include "debug.h"
extern host *pheadhost;

/***
 * Load the list of ip and ports from the hard disk
 */
int load_config(void)
{
	char *line = NULL;
	int linecount = 0;
	int version = 0;
	unsigned short int waitHost = TRUE;
	size_t len = 0;
	__ssize_t read;
	FILE *file = fopen(CONF_FILE, "r");

	if (file == NULL)
	{
		sprintf_log(DEBUG_ERROR, "Unable to read from %s", CONF_FILE);
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
				sprintf_log(DEBUG_ERROR, "%s:%d -> duplicate version tag.", CONF_FILE, linecount);
				exit(0);
			}

			if (!isdigit(line[3]))
			{
				// Our version tag is not a numerical value, single digit in this case.
				sprintf_log(DEBUG_ERROR, "%s:%d -> version %c is not numeric",  CONF_FILE, linecount, line[3]);
				exit(0);
			}
			// the version of our database is too old to continue in this way.
			if ((int)line[3] < CONF_VERSION)
			{
				sprintf_log(DEBUG_ERROR, "%s:%d config version [%d] is too old (expected %d). Please see UPGRADE.TXT",  CONF_FILE, linecount, line[3], CONF_VERSION);
				exit(0);
			}

			version = (int)line[3];
			continue;
		} // end of version tag

		if ((line[0] == '!') && (line[1] == 'D') && line[2] == ':') // debug level!
		{
			int userDebugLevel=0;

			if (sscanf(line, "!D:%d", &userDebugLevel) == 0)
			{
				sprintf_log(DEBUG_WARNING, "%s:%d debug level not numberic; using default.", CONF_FILE, linecount);
				continue;

			}

			// we appear to have an integer debug level, not necessarily valid
			if (userDebugLevel > 0)
			{ 
				char levelchars[10]; // to store our printable debug level

				int remainder = userDebugLevel;

				// check all valid legit level
				if ((userDebugLevel & DEBUG_NOTICE) != 0)
				{
					strcat(levelchars, "N");
					remainder &= ~DEBUG_NOTICE;
				}

				if ((userDebugLevel & DEBUG_ERROR) != 0)
				{
					strcat(levelchars, "E");
					remainder &= ~DEBUG_ERROR;
				}

				if ((userDebugLevel & DEBUG_WARNING) != 0)
				{
					strcat(levelchars, "W");
					remainder &= ~DEBUG_WARNING;
				}

				if ((userDebugLevel & DEBUG_INFO) != 0)
				{
					strcat(levelchars, "I");
					remainder &= ~DEBUG_INFO;
				}

				if ((userDebugLevel & DEBUG_DEBUG) != 0)
				{
					strcat(levelchars, "D");
					remainder &= ~DEBUG_DEBUG;
				}
				if ((userDebugLevel & DEBUG_TRACE) != 0)
				{
					strcat(levelchars, "T");
					remainder &= ~DEBUG_TRACE;
				}

				// if we have remainders someone fucked up their math.
				if (remainder > 0)
				{
					sprintf_log(DEBUG_WARNING, "%s:%d debug level contains unknown values, skipping.", CONF_FILE, linecount);
					continue;
				}

				sprintf_log(DEBUG_INFO, "%s:%d set debug levels [%s]", CONF_FILE, linecount, levelchars);
				debugLevel = userDebugLevel;

				continue;
			}
			
			continue;
		}

		char *token = strtok(line, " "); // seperate by space
		host *curr;
		

		while (token != NULL)
		{
			// We are waiting for a hostname (ie: newline)
			if (waitHost)
			{
				// dtui
				if (strlen(token) > (sizeof(pheadhost->hostname) -1))
				{
					sprintf_log(DEBUG_ERROR, "%s:%d > Size of hostname exceeds allowed characters: %lu of max %d", CONF_FILE, linecount, strlen(token), DNS_SIZE);
					exit(1);
				}

				if (!valid_hostname(token))
				{
					sprintf_log(DEBUG_ERROR, "%s:%d > Hostname '%s' has invalid characters", CONF_FILE, linecount, token);
					exit(1);
				}

				// cycle and make sure we only have valid characters

				curr = addhost(token);
				sprintf_log(DEBUG_INFO, "host add: %s", curr->hostname);
				waitHost = 0; // mark that we are waiting for a port now
			
				
			}  

			// We are not waiting for a hostname, assume (but verify) its a port list
			else
			{
			//	size_t s;
				
			//	s = strlen(token) - 1;

				// cycle through and confirm we are only a number, deal with bounds later.
				for (size_t k = 0; token[k] != '\0'; k++)
				{
					//there is probably a cleaner way of doing all this... we will save it for when
					// i actually know wtf im doing in this language (aka v2)
					if (token[k] == '\n')
					{
						break;
					}

					else if (isspace(token[k]))
					{
						sprintf_log(DEBUG_ERROR, "%s:%d > Host %s contains erroneous whitespaces'", CONF_FILE, linecount, curr->hostname);
						exit(1);
					}
					else if (!isdigit(token[k]) && ((token[k] != '\0')))
					{
						sprintf_log(DEBUG_ERROR, "%s:%d > Host %s contains non-numeric port '%s'", CONF_FILE, linecount, curr->hostname, token);
						exit(1);
					}

					else if (token[k-1] == '\0')
						break; 
					
				}

				// valid port if we havn't died
				// the following if/else is a display rewrite only for adding port ALL
			//	if ((!strncmp(token, "", 1)) && (atoi(token) == 0))
				if (atoi(token) == 0)
				{
					sprintf_log(DEBUG_INFO, "Adding: %s:*all ... ", curr->hostname);
					curr->is_wildcard = TRUE;

					if (curr->totalports > 0)
						sprintf_log(DEBUG_INFO, "[usurps %d previous ports] ", curr->totalports);
				}

				else
					sprintf_log(DEBUG_INFO, "Adding: %s:%s ... " , curr->hostname, token);

				if ((atoi(token) < 0) || (atoi(token) > 65535)) // not a normal port
				{
					sprintf_log(DEBUG_ERROR, "Failed: %s port %d is outside range of 0(all) or 1-65535", curr->hostname, atoi(token));
					exit(1);
				}
				// real work
				if ((curr->is_wildcard) && (atoi(token) > 0))
					sprintf_log(DEBUG_WARNING, "Failed: %s port %d Already applied via '0' entry", curr->hostname, atoi(token));

				else if (addport(curr, atoi(token)))
				{
					sprintf_log(DEBUG_INFO, "Success: %s - %d/%d ports", curr->hostname, curr->totalports, MAX_PORTS);
				}

				else
				{
					if (curr->totalports == MAX_PORTS)
						sprintf_log(DEBUG_WARNING, "Fail: %s max ports for this host reached!", curr->hostname);
				}

			}		
			token = strtok(NULL, " ");
		}
	}

	return OK;
}

int valid_hostname(const char *host)
{
	size_t len = strlen(host);

	if (len < 3)
		return FALSE;

	size_t i = 0;

	while (host[i] != '\0')
	{
		if (!isalpha(host[i]) && (host[i] != '-') && (host[i] != '.'))
			return FALSE;

		i++;
	}

	return TRUE;
}
