

/* Just some favorites */
#define FAILED 0
#define OK 1
#define TRUE 1
#define FALSE 0 



int process_cli_args(int argc, char *argv[]);
void process_cli_help(void);
void process_cli_help_param(char *topic);
void run_dns_updates(host *head);
//#define FULL_VERSION (MAJOR_VERSION + MINOR_VERSION + PATCH_VERSION + TAG_VERSION)
/* #define FULL_VERSION ((sprintf("%d.%d.%d-%s", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, TAG_VERSION))) */

