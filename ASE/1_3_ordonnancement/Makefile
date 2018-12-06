# $Id: Makefile 78 2007-05-21 17:33:37Z skaczmarek $
##############################################################################
ROOTDIR=.

CC	= gcc
CFLAGS	= -Wall -pedantic
CFLAGS  += -g
INCS    = -I$(ROOTDIR)/include
LIBS    = -L$(ROOTDIR)/lib -lhardware

###------------------------------
### Main rules
###------------------------------------------------------------
yield :tmr.o yield.o
	$(CC) $(CFLAGS) -o yield yield.o tmr.o $(LIBS)
tmr.o :tmr.c include/hardware.h include/tmr.h
	$(CC) $(CFLAGS) $(INCS) -c tmr.c
yield.o: yield.c include/yield.h include/tmr.h
	$(CC) $(CFLAGS) $(INCS) -c yield.c

###------------------------------
### Misc.
###------------------------------------------------------------
.PHONY: clean realclean depend
clean:
	$(RM) *.o
realclean: clean
	$(RM) tmr
