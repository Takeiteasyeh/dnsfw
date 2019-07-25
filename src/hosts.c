#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "hosts.h"


int addport(host *selected, int port)
{
	int total = selected->totalports;
	// do not exceed our buffer
	if (total == MAX_PORTS)
		return 0;

	// ensure our port falls within actual port limits
	if ((port < 1) || (port > 65535))
		return 0;

	// lets continue at this point and add the port to index
	selected->ports[total] = port;
	selected->totalports++;

	return 
}
/***
 * Im tired of fucking with this code... addhost is called for even the head host. we will figure that
 * shit out in this block since creating objects and creating pointers in different locations of the
 * detached script is breaking things, including me. -rlynk
 */
host *addhost(host *head, char *name)
{
	// just incase you play with my memory, ill double check here too.
	if (strlen(name) > DNS_SIZE)
	{
		printf("error: dns name exceeds rfc standard of 253 characters (now: %lu)\n", strlen(name));
		exit(1);
	}

	host *parent = head;
	host *current;

	// if this is the first entry we dont do next things
	if (strlen(parent->hostname) == 0)
	{

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
		printf("Not enough memory %s\n", "oops");
		exit(1);
	}

//	current = parent->next;

	strcpy(parent->next->hostname, name);
	parent->next->next = NULL;
	parent->next->totalports = 0;

	return parent->next;

}

