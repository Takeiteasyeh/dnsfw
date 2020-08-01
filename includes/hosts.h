/*                                                       )
          ,%,                                     ) _(___[]_
          %%%,&&&, dnsfw.3rad.ca       ,%%,      (;`       /\
          %Y/%&&&&  rlynk@3rad.ca      %%%%   ___/_____)__/ _\__     ,%%,
        ^^^||^&\Y&^^^^^^^^^^^^^^^^^^^^^%Y/%^^/ (_()   (  | /____/\^^^%%%%^^
          `    || _,..=xxxxxxxxxxxx,    ||   |(' |LI (.)I| | LI ||   %\Y%
         -=      /L_Y.-"""""""""`,-n-. `    @'---|__||___|_|____||_   ||
        ___-=___.--'[========]|L]J: []\ __________@//@___________) )______
       -= _ _ _ |/ _ ''_ " " ||[ -_ 4 |  _  _  _  _  _  _  _  _  _  _  _
                '-(_)-(_)----'v'-(_)--'
       jgs-----------------------------------------------------------------
*/
#define HOSTSH 1 // ;loaded

#define DNS_SIZE 253 // 253 is max length of full domain name including dots.
#define IP_SIZE 16 // 16 max chars for a ipv4 (fuck you ipv6)
#define MAX_PORTS 50 // max ports per host


typedef struct Host
{
	struct Host *next, *prev;
	char hostname[DNS_SIZE + 1];
	char currentIp[IP_SIZE + 1];
	unsigned short ports[MAX_PORTS +1];
	unsigned short int totalports;
	unsigned short int is_wildcard : 1;
} host;


host *pheadhost;
host *addhost(char *name);
int addport(host *selected, int port);

int ip_modified(struct Host *);
char *resolve(char *host);

