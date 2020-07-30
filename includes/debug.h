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
    #define DEBUG_NONE		0x00
    #define DEBUG_NOTICE 	0x01 //notice
    #define DEBUG_ERROR 	0x02 //error, console warn, will always die!
    #define DEBUG_WARNING 0x04
    #define DEBUG_INFO 		0x08
    #define DEBUG_DEBUG 	0x10
    #define DEBUG_TRACE 	0x20
    #define DEBUG_ALL		(DEBUG_NOTICE | DEBUG_ERROR | DEBUG_WARNING | DEBUG_INFO | DEBUG_DEBUG | DEBUG_TRACE)
    #define DEBUG_DEFAULTS	(DEBUG_NOTICE | DEBUG_ERROR | DEBUG_INFO | DEBUG_WARNING )

    // CURRENT DEBUG LEVEL
    #define DEBUG_LEVEL		DEBUG_DEFAULTS

    void to_log(int level, char *message);
    void sprintf_log(int level, char *format, ...);
    char *levelname(int level);