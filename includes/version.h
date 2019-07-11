#include <stdio.h>
#define VERSION_FORMAT "%d.%d.%d-%s"
#define VERSION_MAJOR 0
#define VERSION_MINOR 1
#define VERSION_PATCH 0
#define VERSION_TAG "prealpha"

typedef struct Version
{
	int major;
	int minor;
	int patch;
	char *tag[32];
} version;

const char *getversion(void);


