# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

DEPS=Money.h:Change.h
GTEST_INCLUDE=${GTEST}/include

all: Hash.o

Hash.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ -L${GLOG_LIB} -lglog -I ${DEPS} -iquote ${GTEST_INCLUDE} -iquote ${DEPS} *.cpp -o Hash.o

clean:
	rm Hash.o
