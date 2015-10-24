# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

DEPS=Nearest.h
GTEST_INCLUDE=${GTEST}/include

all: Nearest.o

Nearest.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ -L${GLOG_LIB} -lglog -I ${DEPS} -iquote ${GTEST_INCLUDE} Nearest.cpp NearestTest.cpp -o Nearest.o ${GTEST}/make/gtest_main.a

clean:
	rm Nearest.o
