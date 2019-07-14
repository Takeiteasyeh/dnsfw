#define DEBUG_NONE		0x00;
#define DEBUG_FATAL 	0x01 //fatal, console warn
#define DEBUG_ERROR 	0x02 //error
#define DEBUG_WARNING 	0x04
#define DEBUG_INFO 		0x08
#define DEBUG_DEBUG 	0x10
#define DEBUG_TRACE 	0x20
#define DEBUG_ALL		(DEBUG_FATAL & DEBUG_ERROR & DEBUG_WARNING & DEBUG_INFO & DEBUG_DEBUG & DEBUG_TRACE)
#define DEBUG_DEFAULTS	(DEBUG_FATAL & DEBUG_ERROR)

/* Just some favorites */
#define FAILED 0
#define OK 1
#define TRUE 1
#define FALSE 0 



int process_cli_args(int argc, char *argv[]);
void process_cli_help(void);
void process_cli_help_param(char *topic);
//#define FULL_VERSION (MAJOR_VERSION + MINOR_VERSION + PATCH_VERSION + TAG_VERSION)
/* #define FULL_VERSION ((sprintf("%d.%d.%d-%s", MAJOR_VERSION, MINOR_VERSION, PATCH_VERSION, TAG_VERSION))) */

