#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include<sys/types.h>
#include "hosts.h"
#include "dnsfw.h"
#include "debug.h"


int addport(host *selected, int port)
{
	int total = selected->totalports;
	// do not exceed our buffer
	if (total == MAX_PORTS)
		return FAILED;

	if (port == 0)
	{
		if (selected->totalports > 0)
		for (int i = 0; i < selected->totalports; i++)
		{
			selected->ports[i] = 0;
		}

		// reset our count
		selected->totalports = 1;

		return OK;
	}
	// ensure our port falls within actual port limits
	if ((port < 1) || (port > 65535))
		return FAILED;

	// lets continue at this point and add the port to index
	selected->ports[total] = port;
	selected->totalports++;
	selected->ports[++total] = '\0';

	return OK;
}
/***
 * Im tired of fucking with this code... addhost is called for even the head host. we will figure that
 * shit out in this block since creating objects and creating pointers in different locations of the
 * detached script is breaking things, including me. -rlynk
 */
host *addhost(char *name)
{
	// just incase you play with my memory, ill double check here too.
	if (strlen(name) > DNS_SIZE)
	{
		sprintf_log(DEBUG_ERROR, "error: dns name exceeds rfc standard of 253 characters (now: %lu)", strlen(name));
		exit(1);
	}

	//host *current;

	// are we initialized yet? // this code should be removed as i think its useless now
	if (pheadhost == NULL)
		pheadhost = malloc(sizeof(host));

	host *parent = pheadhost;
	
	// if this is the first entry we dont do next things
	if (strlen(parent->hostname) == 0)
	{
		strncpy(parent->hostname, name, sizeof(parent->hostname) - 1);
		strcpy(parent->currentIp, "0");
		parent->prev = NULL;
		parent->next = NULL;
		parent->totalports = 0;
		parent->is_wildcard = FALSE;

		return parent;

	}

	while (parent->next != NULL)
	{
		parent = parent->next;
	}

	// end of the list
	parent->next = malloc(sizeof(host));

	if (parent->next == NULL)
	{
		//memory error
		sprintf_log(DEBUG_ERROR, "Not enough memory");
		exit(1);
	}

	strncpy(parent->next->hostname, name, sizeof(parent->hostname));
	strcpy(parent->next->currentIp, "0");
	parent->next->next = NULL;
	parent->next->totalports = 0;
	parent->next->is_wildcard = FALSE;

	return parent->next;

}

char *resolve(char *host)
{
	struct hostent *he;
	struct in_addr **addr_list;

	he = gethostbyname(host); //this is obsolete

	// an error occured, add logging at some time in the future
	if (he == NULL)
		return NULL;

	addr_list = (struct in_addr **)he->h_addr_list;

	/* multiple returns from dns is
	 * a security risk, and somewhat contrary to dynamic dns */
	if (addr_list[1] != NULL)
	{
		//to_log(DEBUG_WARNING, "multiple ips for host");
		return NULL;
	}

	return inet_ntoa(*addr_list[0]);
}


