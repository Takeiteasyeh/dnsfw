#define DNS_SIZE 253 // 253 is max length of full domain name including dots.
#define IP_SIZE 16 // 16 max chars for a ipv4 (fuck you ipv6)

typedef struct Host
{
	struct Host *next, *prev;
	char hostname[DNS_SIZE + 1];
	char currentIp[IP_SIZE + 1];
	char lastIp[IP_SIZE + 1];
	int ports[MAX_PORTS +1];
} host;

host CreateHost(char *, int[]);
int HasIpChanged(struct Host *);

