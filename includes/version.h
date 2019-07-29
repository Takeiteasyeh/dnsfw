#include <stdio.h>
#include <assert.h>
#define VERSION_FORMAT "%d.%d.%d-%s"
#define VERSION_MAJOR 1
#define VERSION_MINOR 0
#define VERSION_PATCH 0
#define VERSION_TAG "alpha1"

typedef struct Version
{
	int major;
	int minor;
	int patch;
	char *tag[32];
} version;

const char *getversion(void);


