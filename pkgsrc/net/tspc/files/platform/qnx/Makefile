#----- Makefile ---------------------------------------------------------------
#
# Makefile,v 1.5 2004/07/02 17:53:40 jpdionne Exp
#
# This source code copyright (c) Hexago Inc. 2002-2004.
#
# This program is free software; you can redistribute it and/or modify it 
# under the terms of the GNU General Public License (GPL) Version 2, 
# June 1991 as published by the Free  Software Foundation.
#
# This program is distributed in the hope that it will be useful, 
# but WITHOUT ANY WARRANTY;  without even the implied warranty of 
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
# See the GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License 
# along with this program; see the file GPL_LICENSE.txt. If not, write 
# to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, 
# MA 02111-1307 USA
#


include ../../Mk/mk-$(target).mk

OBJDIR=../../objs
OBJ=$(OBJDIR)/tsp_local.o
OBJLINK=$(OBJDIR)/*.o
BIN=../../bin
TSPC=tspc

CFLAGS=-lsocket -g -Wall -I../../include -I../../platform/$(target)
CC=gcc

all: $(OBJ) $(OBJLINK) $(BIN)/$(TSPC)

$(OBJDIR)/tsp_local.o:tsp_local.c
	$(CC) $(CFLAGS) -c tsp_local.c -o $(OBJDIR)/tsp_local.o $(DEFINES)

$(BIN)/$(TSPC): $(OBJ)
	$(CC) $(CFLAGS) -o $(BIN)/$(TSPC) $(OBJLINK)

clean:
	rm -f $(OBJDIR)/*.o $(BIN)/$(TSPC)

install: all
