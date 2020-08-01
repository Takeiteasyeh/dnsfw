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
 #include <stdlib.h>
 #include "iptables.h"
 #include "debug.h"

void iptables_initialize_blocks(const int is_destroy)
{
	char cmd[700];
	char *p;
	char *addremove;

	if (is_destroy == 0)
		addremove = "A";
	
	else
		addremove = "D";
	
	
	p = cmd;
	sprintf_log(DEBUG_INFO, "%s default firewall rules", (is_destroy == 1 ? "removing" : "setting"));

	sprintf(cmd, IPTF_DEFAULT_ESTABLISHED, addremove);
	to_log(DEBUG_TRACE, cmd);
	system(p);

	sprintf(cmd, IPTF_DEFAULT_OUTBOUND, addremove);
	to_log(DEBUG_TRACE, cmd);
	system(p);

	sprintf(cmd, IPTF_DEFAULT_ICMP, addremove);
	to_log(DEBUG_TRACE, cmd);
	system(p);

	sprintf(cmd, IPTF_DEFAULT_REJECT_INPUT, addremove);
	to_log(DEBUG_TRACE, cmd);
	system(p);

	sprintf(cmd, IPTF_DEFAULT_REJECT_FORWARD, addremove);
	to_log(DEBUG_TRACE, cmd);
	system(p);

	sprintf_log(DEBUG_INFO, "default firewall rules %s.", (is_destroy == 1 ? "removed" : "added"));
}

 void iptables_add(char *ip, int port)
 {
	 //FILE *p;

	 char cmd[700];
	 char *p;
	 p = cmd;

	 if (port == 0)
	 {
		 sprintf(cmd, IPTF_ADD_FULL, ip);
		 //puts(p);
		 to_log(DEBUG_TRACE, cmd);
		 system(p);

	 }
	 
	 else
	 {
	 	sprintf(cmd, IPTF_ADD_ONE, ip, "tcp", port);
		to_log(DEBUG_TRACE, cmd);
		//puts(p);
		system(p);

		sprintf(cmd, IPTF_ADD_ONE, ip, "udp", port);
		//puts(p);
		to_log(DEBUG_TRACE, cmd);
		system(p);
	 }

	return; //system(cmd);
 }

 void iptables_del(char *ip, int port)
 {
	 char cmd[700];
	 char *p;
	 p = cmd;

	 if (port == 0)
	 {
		 // full applies to both protocols and is omitted.
		 sprintf(cmd, IPTF_DEL_FULL, ip); 
		// puts(p);
		to_log(DEBUG_TRACE, cmd);
		 system(p);

	 }
	 
	 else
	 {
	 	sprintf(cmd, IPTF_DEL_ONE, ip, "tcp", port);
		to_log(DEBUG_TRACE, cmd);
		system(p);
		sprintf(cmd, IPTF_DEL_ONE, ip, "udp", port);
		to_log(DEBUG_TRACE, cmd);
		system(p);
	 }

	return; //system(cmd);
 }