/*
---------------------------------------------------------------------------
 tsp_local.c,v 1.1 2004/03/25 18:33:00 jpdionne Exp
---------------------------------------------------------------------------
Copyright (c) 2001-2003 Hexago Inc. All rights reserved.

     The contents of this file are subject to the Hexago
     Public License Version 1.0 (the "License"); you may not
     use this file except in compliance with the License.

     Software distributed under the License is distributed on
     an "AS IS" basis, WITHOUT WARRANTY OF ANY KIND, either
     express or implied. See the License for the specific
     language governing rights and limitations under the
     License.

     The Original Code is _source code of the tunnel server
     protocol-client side_.

     The Initial Developer of the Original Code is Hexago .

     All Rights Reserved.

     Contributor(s): ______________________________________.

---------------------------------------------------------------------------
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#include <sys/types.h>
#include <sys/wait.h>

#define _USES_SYS_SOCKET_H_
#define _USES_SYS_TIME_H_
#define _USES_NETINET_IN_H_
#define _USES_ARPA_INET_H_

#include "platform.h"

/* get data types needed here */

#include "config.h"	/* tConf */
#include "xml_tun.h" /* tTunnel */
#include "net.h"	/* net_tools_t */
#include "tsp_net.h"/* tspClose */
#include "tsp_client.h"/*tspmain*/
#include "net_ka.h"

/* some globals and the logging */

#include "lib.h"
#include "log.h"
#include "errors.h"

//#include "tsp_tun.h"   /* linux's tun */
#include "tsp_setup.h"

/* these globals are defined by US used by alot of things in  */

char *FileName  = "tspc.conf";
char *LogFile   = "tspc.log";
char *LogFileName = NULL;
char *ScriptInterpretor = "/bin/sh";
char *ScriptExtension = "sh";
char *ScriptDir = NULL;
char *TspHomeDir = "/usr/local/etc/tsp";
char DirSeparator = '/';

int Verbose = 0;
int RootUid = 0;


/* linux specific to setup an env variable */

void
tspSetEnv(char *Variable, char *Value, int Flag)
{
    if(Verbose) printf("%-30.30s   %s\n", Variable, Value);
     setenv(Variable, Value, Flag);
}

/* tspSetupTunnel() will callback here */

char *
tspGetLocalAddress(int socket) 
{
	struct sockaddr_in addr;
	int len;
	char *buf;

	len = sizeof addr;
	if (getsockname(socket, (struct sockaddr *)&addr, &len) < 0) {
		Display(1, ELError, "TryServer", "Error while trying to find source ip address.");
		return NULL;
	}
	
	buf = inet_ntoa(addr.sin_addr);
	return buf;
}


/* tspSetupTunnel() will callback here */

/* start locally, ie, setup interface and any daemons or anything needed */

int tspStartLocal(int socket, tConf *c, tTunnel *t, net_tools_t *nt)
{
	  int status;
	  int keepalive_interval = 0;

	  /* Test for root privileges */
	  if(geteuid() != 0) {
		  Display(0, ELError, "tspStartLocal", "FATAL: You must be root to setup a tunnel");
		  return INTERFACE_SETUP_FAILED;
	  }
	  
	/* start the tunneler service */

	 if (t->keepalive_interval != NULL) {
		keepalive_interval = atoi(t->keepalive_interval);
		Display(3, ELInfo, "tspStartLocal", "keepalive interval: %s\n", t->keepalive_interval);
	 }
	 
	  {
		int tunfd;

		Display(0, ELInfo, "tspStartLocal", "Going daemon, check %s for tunnel creation status", LogFile);

		if (daemon(1, 0) == -1) {
			Display(1, ELError, "tspStartLocal", "Unable to fork.");
			return INTERFACE_SETUP_FAILED;
		}

		if (strcasecmp(t->type, STR_CONFIG_TUNNELMODE_V6UDPV4) == 0 ) {
			Display(1, ELError, "tspStartLocal", "v6udpv4 (NAT traversal) is not supported with this platform");
				return(INTERFACE_SETUP_FAILED);
		}
		
		/* now, run the config script without 
		   giving it our tunnel file descriptor.

		   This is important because otherwise
		   the tunnnel will stay open even if we get killed
		   */

		{
			int pid = fork();
			if (pid < 0)
				// fork() error
				return INTERFACE_SETUP_FAILED;

			else if (pid == 0) {	// child
				close(tunfd);
				if (tspSetupInterface(c, t) != 0)
					exit(INTERFACE_SETUP_FAILED);
				exit(0);
			}

			else {	//parent
				int s = 0;
				Display(1, ELInfo, "tspStartLocal", "Waiting for setup script to complete");
				if (wait(&s) == pid) { // ok our child returned 
					if ( !WIFEXITED(s) ) {
						Display(0, ELError, "tspStartLocal", "Script failed to execute correctly");
						return INTERFACE_SETUP_FAILED;
					}
					if ( WEXITSTATUS(s) != 0 ) {
						Display(0, ELError, "tspStartLocal", "Script failed to execute correctly");
						return INTERFACE_SETUP_FAILED;
					}
					// else everything is fine
				}
				else { // error occured we have no other child
					Display(1, ELError, "tspStartLocal", "Error while waiting for script to complete");
				return INTERFACE_SETUP_FAILED;
				}
			}
		}

		if (keepalive_interval == 0)
			/* if there is no keepalive,
			   we can exit safe at this point */
			return NO_ERROR; 

		status = NetKeepaliveV6V4Tunnel(t->client_address_ipv6,
						t->keepalive_address_ipv6,
						keepalive_interval);
				return status;
	}
	
	return INTERFACE_SETUP_FAILED; /* should never reach here */
}


int main(int argc, char *argv[]) 
{

	/* entry point */
	
	return tspMain(argc, argv);
	
}
	
	

