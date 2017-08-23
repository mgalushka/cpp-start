# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

DEPS=Median.h
GTEST_INCLUDE=${GTEST}/include

all: Median.o

Median.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-stdlib=libc++ -L${GLOG_LIB} -lglog -I ${DEPS} -iquote ${GTEST_INCLUDE} \
	MedianTest.cpp -o MedianTest.o ${GTEST}/make/gtest_main.a

clean:
	rm MedianTest.o
