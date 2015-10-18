CC=g++
DEPS = Nearest.h

all: Nearest.o

Nearest.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -I ${DEPS} Nearest.cpp -o Nearest.o

clean:
	rm Nearest.o
