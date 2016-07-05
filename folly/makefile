# static compile with google test library
CC=g++
GTEST=~/Documents/projects/googletest/googletest
GLOG_LIB=/usr/local/lib

FOLLY_VERSION=0.57.0
FOLLY_LIB=/usr/local/Cellar/folly/${FOLLY_VERSION}/lib/libfolly.a
DOUBLE_CONVERSION_LIB=/usr/local/Cellar/double-conversion/1.1.5/lib/libdouble-conversion.a

DEPS=FollyExperiment.h
GTEST_INCLUDE=${GTEST}/include

all: FollyExperiment.o FollyJson.o

FollyJson.o:
	${CC} -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-stdlib=libc++ -L${GLOG_LIB} -lglog FollyJson.cpp \
	-o FollyJson.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

FollyExperiment.o:
	${CC} -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-stdlib=libc++ -L${GLOG_LIB} -lglog -iquote ${DEPS} FollyExperiment.cpp \
	-o FollyExperiment.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

clean:
	rm -f FollyExperiment.o
	rm -f FollyJson.o
