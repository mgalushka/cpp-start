# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

DEPS=Vector.h
GTEST_INCLUDE=${GTEST}/include

all: VectorTest.o

VectorTest.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-stdlib=libc++ -L${GLOG_LIB} -lglog -I ${DEPS} -iquote ${GTEST_INCLUDE} \
	-iquote ${DEPS} Vector.cpp VectorTest.cpp -o VectorTest.o ${GTEST}/make/gtest_main.a

clean:
	rm VectorTest.o
