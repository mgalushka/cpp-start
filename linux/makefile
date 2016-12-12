# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

# Common temp files to delete from each directory.
TEMPFILES=core core.* *.o temp.* *.out

ROOT=.

EXTRALIBS=-lrt

DEPS=apue.h

CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LDFLAGS=
LDDIR=-L$(ROOT)/lib
LDLIBS=$(LDDIR) -lapue $(EXTRALIBS)
CFLAGS=-ansi -I$(ROOT)/include -Wall -DLINUX -D_GNU_SOURCE $(EXTRA)
RANLIB=echo
AR=ar
AWK=awk


PROGS =	ls

all:	$(PROGS)

%:	%.c $(LIBAPUE)
	$(CC) $(CFLAGS) -I ${DEPS} $@.c -o $@ $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(PROGS) $(MOREPROGS) $(TEMPFILES) *.o xlate rot13c2.c
