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
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include "debug.h"
#include "config.h"

extern int debugLevel;


// just a shortcut to sprintf_log
void to_log(int level, char *message)
{
	sprintf_log(level, message);
	return;
}

/***
 * Write a formatted string, matching the given debug level,
 * to the logfile specified in config.h
 */
void sprintf_log(int level, char *format, ...)
{
	va_list parg;
	char buffer[5024];
	char prebuffer[1024];
	char timebuff[200];
	char timebuff2[200];

	if ((level & debugLevel) == 0)
	{
		return;
	}
/*	if ((level & DEBUG_LEVEL) == 0)
	{
		return;
	} */

	FILE *fptr;

	time_t ltime;
	ltime = time(NULL);

	va_start(parg, format);
	size_t buffsize = 1024;
	buffsize = vsnprintf(prebuffer, buffsize - 1, format, parg);

	sprintf(timebuff, "%s", (asctime(localtime(&ltime))));
	snprintf(timebuff2, strlen(timebuff), "%s", timebuff);

	char *lname;
	lname = levelname(level);

	snprintf(buffer, sizeof(buffer) -1, "[%s]<%c> %s\n", timebuff2, lname[0], prebuffer);
	
	// try to write system side first
	fptr = fopen(CONF_LOG_PREFIX CONF_LOG, "a");

	if (fptr == NULL)
	{
		fptr = fopen(CONF_LOG, "a");

		if (fptr == NULL)
			printf("Unable to write to log file: %s\n", CONF_LOG);
	}

	else
	{
		fwrite(buffer, 1, strlen(buffer) +1, fptr);
		fclose(fptr);
	}

	va_end(parg);
}

/***
 * Return a string of the matching debug level.
 */
char *levelname(int level)
{
	char *type = NULL;

	switch (level)
	{
		case DEBUG_NONE:
			type = "None";
			break;

		case DEBUG_NOTICE:
			type = "Notice";
			break;

		case DEBUG_ERROR:
			type = "Error";
			break;

		case DEBUG_WARNING:
			type = "Warn";
			break;

		case DEBUG_INFO:
			type = "Info";
			break;

		case DEBUG_DEBUG:
			type = "Debug";
			break;

		case DEBUG_TRACE:
			type = "None";
			break;

		default:
			type = "undefined";
			break;
	}

	return type;
}