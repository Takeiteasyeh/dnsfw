#include "config.h"

#define DNS_SIZE 253 // 253 is max length of full domain name including dots.
#define IP_SIZE 16 // 16 max chars for a ipv4 (fuck you ipv6)

typedef struct Host
{
	struct Host *next, *prev;
	char hostname[DNS_SIZE + 1];
	char currentIp[IP_SIZE + 1];
	char lastIp[IP_SIZE + 1];
	unsigned short ports[MAX_PORTS +1];
	unsigned short int totalports;
} host;

host *addhost(host *head, char *name);
int addport(host *selected, int port);

int HasIpChanged(struct Host *);

