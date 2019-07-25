    #define DEBUG_NONE		0x00
    #define DEBUG_FATAL 	0x01 //fatal, console warn, will always die!
    #define DEBUG_ERROR 	0x02 //error, console warn, will always die!
    #define DEBUG_WARNING 	0x04
    #define DEBUG_INFO 		0x08
    #define DEBUG_DEBUG 	0x10
    #define DEBUG_TRACE 	0x20
    #define DEBUG_ALL		(DEBUG_FATAL | DEBUG_ERROR | DEBUG_WARNING | DEBUG_INFO | DEBUG_DEBUG | DEBUG_TRACE)
    #define DEBUG_DEFAULTS	(DEBUG_FATAL | DEBUG_ERROR | DEBUG_INFO)

    // CURRENT DEBUG LEVEL
    #define DEBUG_LEVEL		DEBUG_ALL

    void debug(int level, char *file, char *sub, int line, char *message);
    void to_log(int level, char *message);
    char *levelname(int level);