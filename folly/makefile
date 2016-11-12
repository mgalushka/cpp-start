#CC=/usr/local/Cellar/gcc6/6.2.0/bin/g++-6
#CC=/usr/local/Cellar/gcc5/5.4.0/bin/g++-5
#CC=g++
CC=clang

# static compile with google test library
GTEST=~/Documents/projects/googletest/googletest
GLOG_LIB=/usr/local/lib

CLANG_OPTIONS=""

FOLLY_VERSION=2016.09.05.00_1
FOLLY_LIB=/usr/local/Cellar/folly/${FOLLY_VERSION}/lib/libfolly.a
DOUBLE_CONVERSION_LIB=/usr/local/Cellar/double-conversion/1.1.5/lib/libdouble-conversion.a

DEPS=FollyExperiment.h
GTEST_INCLUDE=${GTEST}/include

all: FollyExperiment.o FollyJson.o CopyFolly.o

# -stdlib=libc++

CopyFolly.o:
	${CC} -undefined dynamic_lookup -O1 -fsanitize=address -fno-omit-frame-pointer -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -stdlib=libc++ -std=c++11 \
	-L${GLOG_LIB} -lglog CopyFolly.cpp \
	-o CopyFolly.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

FollyJson.o:
	${CC} -undefined dynamic_lookup -O1 -fsanitize=address -fno-omit-frame-pointer -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-L${GLOG_LIB} -lglog FollyJson.cpp \
	-o FollyJson.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

FollyExperiment.o:
	${CC} -undefined dynamic_lookup -O1 -fsanitize=address -fno-omit-frame-pointer -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-L${GLOG_LIB} -lglog -iquote ${DEPS} FollyExperiment.cpp \
	-o FollyExperiment.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

clean:
	rm -f FollyExperiment.o
	rm -f FollyJson.o
	rm -f CopyFolly.o
