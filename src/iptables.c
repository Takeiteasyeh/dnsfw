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

 int iptables_del(char *host, int port)
 {

	 return 1;
 }