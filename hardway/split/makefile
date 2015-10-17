CC=g++
DEPS = split.h

all: split.o

split.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -I ${DEPS} split.cpp -o split.o

clean:
	rm split.o
