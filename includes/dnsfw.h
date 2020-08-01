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
// #include "hosts.h"

/* Just some favorites */
#define FAILED 0
#define OK 1
#define TRUE 1
#define FALSE 0 

int debugLevel;
int process_cli_args(int argc, char *argv[]);
void process_cli_help(void);
void process_cli_help_param(char *topic);
void run_dns_updates();
void sig_handle(int sig);
void shutdown_gracefully(void);
void restart(void);
void clear_iptable_entries(void);
int has_iptables_restarted(void);
