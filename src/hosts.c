#include <stdlib.h>

#include "../includes/hosts.h"

host newhost(host *head, char *name)
{
	if (strlen(name) > DNS_SIZE)
	{
		printf("error: dns name exceeds rfc standard of 253 characters (now: %d)\n", strlen(name));
		exit(1);
	}

	host *current = head;

	while (current->next != NULL)
	{
		current = current->next;
	}

	// end of the list
	current->next = malloc(sizeof(host));

	if (current->next == NULL)
	{
		//memory error
		exit(1);
	}

	strcpy(current->next->hostname, name);
	current->next->next = NULL;

	return *current;

}

