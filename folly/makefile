# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

FOLLY_LIB=/usr/local/Cellar/folly/0.48.0/lib/libfolly.a
DOUBLE_CONVERSION_LIB=/usr/local/Cellar/double-conversion/1.1.5/lib/libdouble-conversion.a

DEPS=FollyExperiment.h
GTEST_INCLUDE=${GTEST}/include

all: FollyExperiment.o

FollyExperiment.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ -I ${DEPS} -iquote ${DEPS} *.cpp -o FollyExperiment.o ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

clean:
	rm -f FollyExperiment.o
