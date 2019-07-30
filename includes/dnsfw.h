

/* Just some favorites */
#define FAILED 0
#define OK 1
#define TRUE 1
#define FALSE 0 


host headhost;
host *pheadhost;
int process_cli_args(int argc, char *argv[]);
void process_cli_help(void);
void process_cli_help_param(char *topic);
void run_dns_updates();
void sig_handle(int sig);
void shutdown_gracefully(void);
void restart(void);
void clear_iptable_entries(void);
//#define FULL_VERSION (MAJOR_VERSION + MINOR_VERSION + PATCH_VERSION + TAG_VERSION)
/* #define FULL_VERSION ((sprintf("%d.%d.%d-%s", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, TAG_VERSION))) */

