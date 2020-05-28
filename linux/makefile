# Common make definitions, customized for each platform

# Definitions required in all program directories to compile and link
# C programs using gcc.

# Common temp files to delete from each directory.
ROOT=.

EXTRALIBS=-lrt

headers = $(wildcard *.h)

CC=gcc
COMPILE.c=$(CC) $(CFLAGS) $(CPPFLAGS) -c
LINK.c=$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS)
LDFLAGS=
LDLIBS=$(EXTRALIBS)
CFLAGS=-Wall -DLINUX -D_GNU_SOURCE $(EXTRA)
RANLIB=echo
AR=ar
AWK=awk

PROGS =	ls echo mypid env

DEPS = $(headers)

all:	$(PROGS)

%:	%.c $(DEPS)
	$(CC) $(CFLAGS) -iquote $(DEPS) $@.c -o $@.o $(LDFLAGS)

clean:
	rm -f *.o
