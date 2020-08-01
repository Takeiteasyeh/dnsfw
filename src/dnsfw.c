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

#include <stdio.h>
#include <string.h>
#include <stdlib.h> // malloc, calloc, realloc, free
#include <unistd.h>
#include <signal.h>
#include "iptables.h"
#include "config.h"
#include "dnsfw.h"
#include "debug.h"
//#include "hosts.h"
#include "version.h"

//<<<<<<< HEAD
//host headhost = { .currentIp = "0", .next = NULL};
//=======
host headhost = { .currentIp = "0", .next = NULL };
//>>>>>>> v120
host *pheadhost;
char *myexename;
//char lasterror[1024];
//int lastrepeatcount = 0;
int debugLevel = 0; // default debug level is INFO/WARN/ERROR
int forkable = 0;
int block = 0;
	
int main(int argc, char *argv[])
{
	myexename = malloc(sizeof(argv[0]));
	pheadhost = malloc(sizeof(host));
	myexename = argv[0];
//<<<<<<< HEAD
//	pheadhost = &headhost;
//=======
	pheadhost = malloc(sizeof(host));
	pheadhost = &headhost;
	debugLevel = (DEBUG_INFO | DEBUG_ERROR | DEBUG_WARNING);
//>>>>>>> v120

	if (signal(SIGINT, sig_handle) == SIG_ERR)
		to_log(DEBUG_WARNING, "Unable to catch SIGINT");

	if (signal(SIGHUP, sig_handle) == SIG_ERR)
		to_log(DEBUG_WARNING, "Unable to catch SIGHUP handle");

	if (signal(SIGTERM, sig_handle) == SIG_ERR)
		to_log(DEBUG_WARNING, "Unable to catch SIGTERM handle");
//	printf("file: %x", CONFIG_FILE_ORIG);
	sprintf_log(DEBUG_INFO, "-------------------");
	sprintf_log(DEBUG_INFO, "dnsfw v%s starting.", getversion());
	sprintf_log(DEBUG_INFO, "built: %s %s with gcc%d.%d", __DATE__, __TIME__, __GNUC__, __GNUC_MINOR__);
	sprintf_log(DEBUG_INFO, "author: rlynk@3rad.ca - dnsfw.3rad.ca");

	// we need to run as root?
	if (NEEDROOT == FALSE)
		sprintf_log(DEBUG_WARNING, "skipping root check [may cause issues]");

	else if (getuid() > 0)
	{
		printf("Use root\n");
		sprintf_log(DEBUG_ERROR, "error: please run as root, terminating.");
		exit(1);
	}

	// check command line arguments
	if (argc > 1)
	{
		// if process_cli_args returns 0 it means we should exit/
		if (!process_cli_args(argc, argv))
			exit(1);
	}
	
	load_config();

	// do we need to now install default rules?
	if (block)
	{
				// remove open ssh access
	//	sprintf_log(DEBUG_INFO, "fw -> removing emergency 0.0.0.0:ssh");
	//	iptables_del("0.0.0.0", 22);
		iptables_initialize_blocks(0);
	}
	sprintf_log(DEBUG_INFO, "running first cycle");
	run_dns_updates();



	sleep(30);
	
	while (1)
	{
		if (has_iptables_restarted())
		{
			sprintf_log(DEBUG_INFO, "iptables -> pid changed, *NOT* restarting due to bug.");
			//restart();
		}

		run_dns_updates();

		sleep(WAIT_TIME);
	}
}

/**
 * If we return 0, the process will end, return 1 to continue
 */
int process_cli_args(int argc, char *argv[])
{
	int retcode = 0; // by default, any cli arguments are considered fatal to the application

	if ((strncmp(argv[1], "-h", 3) == 0) || (strncmp(argv[1], "--help", 7) == 0))
	{
		if (argc >2 )
			process_cli_help_param(argv[2]);
		
		else
			process_cli_help();
	}

	else if ((strncmp(argv[1], "-g", 3) == 0) || (strncmp(argv[1], "--genconf", 10) == 0))
	{
		printf("genconf\n");
	} 
	
	else if ((strncmp(argv[1], "-f", 3) == 0) || (strncmp(argv[1], "--fork", 6) == 0))
	{
		printf("test block\n");
	} 

/*
	else if ((strncmp(argv[1], "-l", 3) == 0) || (strncmp(argv[1], "--list", 7) == 0))
	{
		printf("test block\n");
	} 

	else if ((strncmp(argv[1], "-a", 3) == 0) || (strncmp(argv[1], "--add", 6) == 0))
	{
		printf("test block\n");
	} 
	
	else if ((strncmp(argv[1], "-r", 3) == 0) || (strncmp(argv[1], "--remove", 9) == 0))
	{
		printf("test block\n");
	} */

	return retcode;
}

void process_cli_help(void)
{
	printf("# bdnsfw: help\n");
	printf("# description: Resolve dynamic dns for automatic firewall updates\n");
	printf("#\n");
	printf("# -h | --help          This screen.\n");
	printf("# -g | --genconf       Generate the first-run ip config.\n");
	printf("# -f | --fork          Fall to background on run.\n");
	printf("# -a | --netconf       Download a configuration file.\n");
	printf("# for more help, use, 'help fork', ect.\n");
	printf("# end of help index.\n");
}

void process_cli_help_param(char *topic)
{
	if (strncmp(topic, "genconf", 8) == 0)
	{
		printf("# bdnsfw: help genconf\n");
		printf("# description: Generate the initial configuration file\n");
		printf("#\n");
		printf("# -g | --genconf      You will be prompted.\n");
	}

	else if (strncmp(topic, "fork", 6) == 0)
	{
		printf("# bdnsfw: help remove\n");
		printf("# description: Remove from the rDNS hosts.\n");
		printf("#\n");
		printf("# -r | --remove [host]      Removes the given host\n");
	}

	else
	{
		printf("# bdnsfw: unknown help topic.\n");
	}
}

/***
 * Perform all the dns lookups and ip checks for
 * iptable modifications.
 */
void run_dns_updates(void)
{
	host *cycle = NULL;
	cycle = pheadhost;

	while (cycle != NULL)
	{
		char *ip = resolve(cycle->hostname);
		int remove = FALSE;
		int preskip = 0;
		
		// if the ip is 0.0.0.0 but hostname isnt than we resolved a real host to 0.0.0.0, which is forbidden.
		if ((strcmp(cycle->hostname, "0.0.0.0") > 0) && (ip != NULL) && (strcmp(ip, "0.0.0.0") == 0))
		{
			sprintf_log(DEBUG_WARNING, "Danger: %s resolves to 0.0.0.0 (all ips) and will be skipped", cycle->hostname, ip, cycle->currentIp);
			ip = NULL; // reset the ip to null for clearing if needed.
			preskip = 1;
		}

		if (ip == NULL)
		{
			// if we dont have a current ip, log and move on
			if (strcmp(cycle->currentIp, "0") == 0)
			{
				if (preskip == 0)
				{
					sprintf_log(DEBUG_INFO, "%s does not resolve, is ipv6, or resolves more than once, skipping.", cycle->hostname);
				}
				
				preskip = 0;
				cycle = cycle->next;
				continue;
				
			}

			//this is a removal without a new entry.
			else
			{
				//wildcard check first
				if (cycle->is_wildcard)
				{
					iptables_del(cycle->currentIp, 0);
					
					sprintf_log(DEBUG_INFO, "%s removed ~all", cycle->hostname);
					strcpy(cycle->currentIp, "0");
					cycle = cycle->next;
					continue;
				}

				// cycle through all our ports,
				for (int i = 0; i < MAX_PORTS; i++)
				{
					// if we hit a null we stop
					if (cycle->ports[i] == '\0')
						break;

					iptables_del(cycle->currentIp, cycle->ports[i]);

					sprintf_log(DEBUG_INFO, "%s removed %d", cycle->hostname, cycle->ports[i]);
				}

				strcpy(cycle->currentIp, "0");
				cycle = cycle->next;
				continue;
			}
		}

		// if new ip is same as current we also continue.
		else if (strcmp(ip, cycle->currentIp) == 0)
		{
			cycle = cycle->next;
			continue;
		}			

		// we need to update this entry
		else
		{
			sprintf_log(DEBUG_INFO, "%s is now %s (old was %s)", cycle->hostname, ip, (cycle->currentIp[0] == '0' ? "not set" : cycle->currentIp));
			// if ip is not 0 we do need to remove old entries
			if (strcmp(cycle->currentIp, "0") != 0)
			{
				remove = TRUE; // just set the flag so we can do it when we cycle ports
			}

			// check if wildcard entry
			if (cycle->is_wildcard)
			{
				// if we are supposed to do a removal first, do it.
				if (remove)
					iptables_del(cycle->currentIp, 0);

				// send it to iptables and then copy ip to our object
				iptables_add(ip, 0);
				strncpy(cycle->currentIp, ip, sizeof(cycle->currentIp) -1);
				sprintf_log(DEBUG_INFO, "`--- updated port: full-access(0)");

				// we MUST continue from here on our loop
				// as having ports as wildcard is undefined.
				cycle = cycle->next;
				continue;
			}

			// cycle through all our ports,
			for (int i = 0; i < cycle->totalports; i++)
			{
				// if we hit a null we stop
				if (cycle->ports[i] == '\0')
					break;

				if (remove)
				{
					iptables_del(cycle->currentIp, cycle->ports[i]);
				}

				iptables_add(ip, cycle->ports[i]);
				sprintf_log(DEBUG_INFO, "`--- updated port: %d", cycle->ports[i]);
			}

			strncpy(cycle->currentIp, ip, sizeof(cycle->currentIp) -1);
		}

		cycle = cycle->next;
	}
}

/***
 * Handle all terminal signals
 */
void sig_handle(int sig)
{
	switch (sig)
	{
		case SIGINT:
		case SIGTERM:
		case SIGKILL:
			to_log(DEBUG_INFO, "performing gracefull shutdown from SIGHANDLE...");
			shutdown_gracefully();
			break; //unreachable code

		case SIGHUP:
			to_log(DEBUG_INFO, "performing restart from sighup...");
			restart();
			break; //unreachable

		default:
			break; // unsupported signal

	}

}

int has_iptables_restarted(void)
{
	FILE *pfile;
	char *line;
	size_t length;
	size_t read;
	static int iptables_pid=0; // current/last pid
//	static int has_error=FALSE; // report errors once
	int pid = 0; // parsed pid
	char b;

	pfile = popen("service iptables status", "r");

	if (!pfile)
		return -1;

	while ((read = getline(&line, &length, pfile)) != -1)
	{
		//printf("%s", line);
		
		//   Main PID: 48718 (code=exited, status=0/SUCCESS)
		if (sscanf(line, "%*s PID: %s %*s", &b))
		{
			pid = atoi(&b);
			pclose(pfile);

			//iif error and recovery, restart
			if (iptables_pid == -1)
				return TRUE;

			// same pid, we are fine
			if (iptables_pid == pid)
				return FALSE;

			// first pid, set and carry on
			if (iptables_pid == 0)
			{
			//	iptables_pid = pid;
				sprintf_log(DEBUG_INFO, "iptables -> found pid: %d", pid);
				iptables_pid = pid;
				return FALSE;
			}

			// pid is different
			else
			{
				iptables_pid = pid;
				return TRUE;
			}
			 
		}
	} 

	pclose(pfile);
	return -1;

}
/***
 * Restart the application. Using this
 * function will prevent a future call to HUP
 * from working.
 */
void restart()
{
	// not quite working as intended..
	return; 

	char *args[]={ NULL};
	// shutdown code, without exit, and then execv to a new instance?
	to_log(DEBUG_INFO, "restart: removing iptable entries...");
	clear_iptable_entries();
	sleep(1);
	to_log(DEBUG_INFO, "restart: usurping process...");
	execv(myexename, args);
	exit(0); // no reach
}

/***
 * Gracefully shutdown the application
 */
void shutdown_gracefully(void)
{
	sprintf_log(DEBUG_INFO, "shutdown: removing iptable entries...");
	clear_iptable_entries();
	sprintf_log(DEBUG_INFO, "shutdown: terminating.");
	exit(0);
}

/***
 * Remove any known valid ip and ports from our
 * ip tables configuration.
 */
void clear_iptable_entries(void)
{
	host *cycle;
	cycle = pheadhost;

	while (cycle != NULL)
	{
		// no ip
		if (strcmp(cycle->currentIp, "0") == 0)
		{
			cycle = cycle->next;
			continue;
		}

		else if (cycle->is_wildcard)
		{
			iptables_del(cycle->currentIp, 0);
			sprintf_log(DEBUG_INFO, "%s:~all removed", cycle->hostname);
		}

		else
		{
			for (int i = 0; i < cycle->totalports; i++)
			{
				if (cycle->ports[i] == '\0')
					break;

				else
				{
					iptables_del(cycle->currentIp, cycle->ports[i]);
					sprintf_log(DEBUG_INFO, "%s:%d removed", cycle->hostname, cycle->ports[i]);
				}
			}
		}

		cycle = cycle->next;
	}

	// we dont remove blocking rules for security reasons. If blocking is set
	// open up ssh on exit for emergency access, but revoke it again next startup.
	if (block)
	{
		iptables_initialize_blocks(1);
		//iptables_add("0.0.0.0", 22);
		//sprintf_log(DEBUG_INFO, "fw -> open emergency 0.0.0.0:ssh due to block=1");
	}
}

void genconf(void)
{
	FILE *file = fopen(CONF_FILE, "r");

	// file aleady exists, we exit at this point to prevent accidents.
	if (file != NULL)
	{
		printf("unable to re-create %s: file exists.", CONF_FILE);
		exit(1);
	}

}
