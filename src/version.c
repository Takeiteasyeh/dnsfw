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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "version.h"
#include "debug.h"

const char *getversion() //pointer return
{
	const size_t lentotal = sizeof(VERSION_MAJOR) + sizeof(VERSION_MINOR) + sizeof(VERSION_PATCH) + sizeof(VERSION_TAG) + 4;

	char *result = malloc(lentotal); // with . - and null term

	if (result == NULL)
	{
		to_log(DEBUG_ERROR, "Error: Unable to allocate memory for version display");
		exit(1);
	}

	int j = snprintf(result, lentotal, VERSION_FORMAT, VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);

	assert(j <= lentotal);
	
	return result;
}