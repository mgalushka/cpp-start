# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

GTEST_INCLUDE=${GTEST}/include

all: TempCopyTest.o

TempCopyTest.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ -L${GLOG_LIB} -lglog -iquote ${GTEST_INCLUDE} *.cpp -o TempCopyTest.o ${GTEST}/make/gtest_main.a

clean:
	rm TempCopyTest.o
