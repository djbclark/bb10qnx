/*
---------------------------------------------------------------------------
 platform.h,v 1.1 2004/03/25 18:33:00 jpdionne Exp
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

/* QNX */

#ifndef _PLATFORM_H_
#define _PLATFORM_H_

#ifdef _USES_SYS_TIME_H_
#include <sys/time.h>
#define GETTIMEOFDAY(A, B) \
	gettimeofday(A, B)
#endif

#ifdef _USES_NETDB_H_
#include <netdb.h>
#endif

#ifdef _USES_SYS_IOCTL_H_
#include <sys/ioctl.h>
#endif

#ifdef _USES_SYS_SOCKET_H_
#include <sys/types.h>
#include <sys/socket.h>
#define SOCKET int
#endif

#ifdef _USES_NETINET_IN_H_
#include <netinet/in.h>
#endif

#ifdef _USES_NETINET_IP6_H_
#include <netinet/ip6.h>
#endif

#ifdef _USES_NETINET_ICMP6_H_
#include <netinet/icmp6.h>
#endif

#ifdef _USES_NET_IF_H_
#include <net/if.h>
#endif

#ifdef _USES_ARPA_INET_H_
#include <arpa/inet.h>
#define INET_PTON(A, B, C)\
	inet_pton(A, B, C)
#endif

#ifdef _USES_SYSLOG_H_
#include <syslog.h>
#define SYSLOG(A,B)\
	syslog(A, B)
#define OPENLOG(A,B,C)\
	openlog(A, B, C)
#define CLOSELOG\
	closelog
#endif


#define SLEEP(A)\
	sleep(A)

#define RANDOM \
	rand
#define SRANDOM \
	srand

/* define u_int_t types */
#include <stdint.h>
#define u_int8_t  uint8_t
#define u_int16_t uint16_t
#define u_int32_t uint32_t

#define SCRIPT_TMP_FILE "/tmp/tspc-tmp.log"

#endif










