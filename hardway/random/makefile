CC=g++

all: Random.o

Random.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ Random.cpp -o Random.o

clean:
	rm Random.o
