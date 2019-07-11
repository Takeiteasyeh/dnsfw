#include <stdlib.h>

#include "../includes/hosts.h"

host CreateHost(char *dns, int *ports)
{
	host Host = {.hostname = "dns.net", .currentIp = "255.255.255.0", .ports = *ports};
	Host.currentIp;

	return Host;
}