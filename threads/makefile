CC=g++

# static compile with google test library
GTEST=~/Documents/projects/googletest/googletest
GLOG_LIB=/usr/local/lib

CLANG_OPTIONS=""

FOLLY_VERSION=2016.09.05.00_1
FOLLY_LIB=/usr/local/Cellar/folly/${FOLLY_VERSION}/lib/libfolly.a
DOUBLE_CONVERSION_LIB=/usr/local/Cellar/double-conversion/1.1.5/lib/libdouble-conversion.a

DEPS=FollyExperiment.h
GTEST_INCLUDE=${GTEST}/include

all: RunThreads.o

# -stdlib=libc++

RunThreads.o:
	${CC} -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 RunThreads.cpp \
	-o RunThreads.o ${GTEST}/make/gtest_main.a

clean:
	rm -f RunThreads.o
