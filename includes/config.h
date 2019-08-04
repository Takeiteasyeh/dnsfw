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
/* If the base database is ever deleted, here is the base version
 * # backup line incase you dont listen to the warning, remove the #...
 * #!V:1
 * # DO NOT REMOVE OR MODIFY THE FOLLOWING LINE OR CORRUPTION COULD OCCUR
 * !V:1
 * # Bacon Dns Firewall Config File
 * # Hashbang represents a comment in this configuration
 * #
 * # Please store as:
 * #
 * # the.rnds.com 23 1000 400
 * #
 * # or, for all ports and proto:
 * #
 * # the.rdns.com 0
 */
#include "hosts.h"
#define CONF_FILE "bdnsfw.conf"
#define CONF_LOG "bdnsfw.log"
#define CONF_VERSION 1 // increment this by 1 every format change, make sure to update the database (somehow)
#define MAX_LINE_SIZE 1024 // (1kb)
#define WAIT_TIME 60 // time to wait between resolves, in seconds

#define MAX_DNS_ENTRIES 50 // max entries to store

#define TYPE_IPTABLES 	0x001
#define TYPE_IPCOP 		0x002

#define FORKING 1 // set to 0 to stay in forground, ie, testing
#define NEEDROOT 1 // set to 0 for basic testing to avoid root check

int load_config(void);