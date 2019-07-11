/*
 * Bacon Dynamic Dns FireWall updater
 * This program comes with absolutely NO WARRANTY
 *
 * Raymond Lynk - rlynk@bacon.place
 * 
 * File: dnsfw.c
 * Info: main run file for the bdnsfw service 
 *
 */

#include <stdio.h>
#include <stdlib.h> // malloc, calloc, realloc, free
#include "../includes/config.h"
#include "../includes/dnsfw.h"
#include "../includes/hosts.h"
extern const char *getversion(void);

int main(void)
{
	printf("dnsfw %s", getversion());
	//printf("dnsfw: v%s\n", FULL_VERSION);	
}


