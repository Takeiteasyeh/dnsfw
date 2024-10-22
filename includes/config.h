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

#include "hosts.h"
#define CONF_FILE_PREFIX "/etc/bacon/"
#define CONF_LOG_PREFIX "/var/log/"
#define CONF_FILE "dnsfw.conf"
#define CONF_LOG "dnsfw.log"
#define CONF_VERSION 3 // increment this by 1 every format change, make sure to update the database (somehow)
#define MAX_LINE_SIZE 1024 // (1kb)
#define WAIT_TIME 120 // time to wait between resolves, in seconds

#define MAX_DNS_ENTRIES 50 // max entries to store

#define TYPE_IPTABLES 	0x001
#define TYPE_IPCOP 		0x002

//#define FORKING 0 // set to 0 to stay in forground, ie, testing
#define NEEDROOT 1 // set to 0 for basic testing to avoid root check

int load_config(void);
int valid_hostname(const char *);
