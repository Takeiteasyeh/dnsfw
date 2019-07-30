 #include <stdio.h>
 #include <stdlib.h>
 #include "iptables.h"

 void iptables_add(char *ip, int port)
 {
	 //FILE *p;

	 char cmd[700];
	 char *p;
	 p = cmd;

	 if (port == 0)
	 {
		 sprintf(cmd, IPTF_ADD_FULL, ip);
		 puts(p);
		 system(p);

	 }
	 
	 else
	 {
	 	sprintf(cmd, IPTF_ADD_ONE, ip, "tcp", port);
		puts(p);
		system(p);
		sprintf(cmd, IPTF_ADD_ONE, ip, "udp", port);
		puts(p);
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
		 puts(p);
		 system(p);

	 }
	 
	 else
	 {
	 	sprintf(cmd, IPTF_DEL_ONE, ip, "tcp", port);
		puts(p);
		system(p);
		sprintf(cmd, IPTF_DEL_ONE, ip, "udp", port);
		puts(p);
		system(p);
	 }

	return; //system(cmd);
 }