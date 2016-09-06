# static compile with google test library
CC=g++
GTEST=~/Documents/projects/googletest/googletest
GLOG_LIB=/usr/local/lib

DEPS=TwoThreads.h
GTEST_INCLUDE=${GTEST}/include

all: TwoThreads.o

TwoThreads.o:
	${CC} -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-stdlib=libc++ -L${GLOG_LIB} -lglog -iquote ${DEPS} TwoThreads.cpp \
	-o TwoThreads.o ${GTEST}/make/gtest_main.a

clean:
	rm -f TwoThreads.o
