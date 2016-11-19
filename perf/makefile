# static compile with google test library
CC=g++
GTEST=~/Documents/projects/googletest/googletest
GLOG_LIB=/usr/local/lib

DEPS=Common.h
GTEST_INCLUDE=${GTEST}/include

all: DoNothing.o DoMap.o DoVector.o

DoNothing.o:
	${CC} -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-iquote ${DEPS} DoNothing.cpp -o DoNothing.o ${GTEST}/make/gtest_main.a

DoMap.o:
	${CC} -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-iquote ${DEPS} DoMap.cpp -o DoMap.o ${GTEST}/make/gtest_main.a

DoVector.o:
	${CC} -v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 \
	-iquote ${DEPS} DoVector.cpp -o DoVector.o ${GTEST}/make/gtest_main.a

clean:
	rm -f DoNothing.o
	rm -f DoMap.o
	rm -f DoVector.o
