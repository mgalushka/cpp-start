# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

GTEST_INCLUDE=${GTEST}/include

all: CachelineTest.o

CachelineTest.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ -L${GLOG_LIB} -lglog -iquote ${GTEST_INCLUDE} CacheLocalityTest.cpp -o CacheLocalityTest.o ${GTEST}/make/gtest_main.a

clean:
	rm CachelineTest.o
