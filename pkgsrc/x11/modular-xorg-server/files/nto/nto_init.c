/*
 * Copyright 1992 by Rich Murphey <Rich@Rice.edu>
 * Copyright 1993 by David Wexelblat <dwex@goblin.org>
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the names of Rich Murphey and David Wexelblat 
 * not be used in advertising or publicity pertaining to distribution of 
 * the software without specific, written prior permission.  Rich Murphey and
 * David Wexelblat make no representations about the suitability of this 
 * software for any purpose.  It is provided "as is" without express or 
 * implied warranty.
 *
 * RICH MURPHEY AND DAVID WEXELBLAT DISCLAIM ALL WARRANTIES WITH REGARD TO 
 * THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND 
 * FITNESS, IN NO EVENT SHALL RICH MURPHEY OR DAVID WEXELBLAT BE LIABLE FOR 
 * ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER 
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF 
 * CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN 
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#ifdef HAVE_XORG_CONFIG_H
#include <xorg-config.h>
#endif

#include <X11/X.h>

#include "compiler.h"

#include "xf86.h"
#include "xf86Priv.h"
#include "xf86_OSlib.h"

#include <sys/utsname.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <errno.h>

static Bool KeepTty = FALSE;
#ifdef __GLIBC__
#define setpgrp setpgid
#endif

#define CHECK_DRIVER_MSG \
  "Check if you started devc-con-hid"

/*
 * Functions to probe for the existance of a supported console driver.
 * Any function returns either a valid file descriptor (driver probed
 * succesfully), -1 (driver not found), or uses FatalError() if the
 * driver was found but proved to not support the required mode to run
 * an X server.
 */
void
xf86OpenConsole()
{
    int i, fd = -1;
    
    if (serverGeneration == 1)
    {
		/* check if we are run with euid==0 */
		if (geteuid() != 0)
		{
			FatalError("xf86OpenConsole: Server must be suid root");
		}
		
		if (!KeepTty)
		{
			/*
			 * detaching the controlling tty solves problems of kbd character
			 * loss.  This is not interesting for CO driver, because it is 
			 * exclusive.
			 */
			setpgrp();
			if ((i = open("/dev/tty",O_RDWR)) >= 0)
			{
				ioctl(i,TIOCNOTTY,(char *)0);
				close(i);
			}
		}
		
		/* detect which driver we are running on */
		fd = open("/dev/console", O_RDWR);
		
		/* Check that a supported console driver was found */
		if (fd < 0)
		{
			FatalError(
					   "%s: No console driver found\n\t%s",
					   "xf86OpenConsole", CHECK_DRIVER_MSG);
		}

		xf86Info.consoleFd = fd;
    }
    return;
}

void
xf86CloseConsole()
{

    close(xf86Info.consoleFd);
    return;
}

int
xf86ProcessArgument(int argc, char *argv[], int i)
{
	/*
	 * Keep server from detaching from controlling tty.  This is useful 
	 * when debugging (so the server can receive keyboard signals.
	 */
	if (!strcmp(argv[i], "-keeptty"))
	{
		KeepTty = TRUE;
		return(1);
	}
	return(0);
}

void
xf86UseMsg()
{
	ErrorF("-keeptty               ");
	ErrorF("don't detach controlling tty (for debugging only)\n");
	return;
}
