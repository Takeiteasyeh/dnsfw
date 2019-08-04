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
#define IPTF_ADD_ONE "iptables -A INPUT -s %s/32 -p %s --dport %d -j ACCEPT\n"
#define IPTF_ADD_FULL "iptables -A INPUT -s %s/32 -j ACCEPT\n"
#define IPTF_DEL_ONE "iptables -D INPUT -s %s/32 -p %s --dport %d -j ACCEPT\n"
#define IPTF_DEL_FULL "iptables -D INPUT -s %s/32 -j ACCEPT\n"
#define IPTABLES_BINARY2 "/sbin/iptables"

void iptables_add(char *ip, int port);
void iptables_del(char *ip, int port);// full applies to both protocols