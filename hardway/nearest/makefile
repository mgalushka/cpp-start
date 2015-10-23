# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
DEPS=Nearest.h
IPATH=${GTEST}/include
BPATH=${GTEST}/make

all: Nearest.o

Nearest.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ -I ${DEPS} -I ${IPATH} -I ${GTEST} -I ${BPATH} -iquote ${IPATH} -B ${BPATH} Nearest.cpp  -o Nearest.o ~/projects/googletest-read-only/make/gtest_main.a

clean:
	rm Nearest.o
