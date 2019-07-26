
#define IPTF_ADD_ONE "iptables -A INPUT -s %s/32 -p %s --dport %d -j ACCEPT\n"
#define IPTF_ADD_FULL "iptables -A INPUT -s %s/32 -j ACCEPT\n"
#define IPTF_DEL_ONE "iptables -D INPUT -s %s/32 -p %s -j ACCEPT\n"
#define IPTF_DEL_FULL "iptables -D INPUT -s %s/32 -p %s -j ACCEPT\n"
#define IPTABLES_BINARY "/sbin/iptables"

void iptables_add(char *host, int port);
int iptables_del(char *host, int port);