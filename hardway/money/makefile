# static compile with google test library
CC=g++
GTEST=~/projects/googletest-read-only
GLOG_LIB=/usr/local/lib

DEPS=Money.h:Change.h
GTEST_INCLUDE=${GTEST}/include

all: MoneyTest.o

MoneyTest.o:
	${CC} -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -std=c++11 -stdlib=libc++ -L${GLOG_LIB} -L/usr/lib -lglog -I ${DEPS} -iquote ${GTEST_INCLUDE} -iquote ${DEPS} *.cpp -o MoneyTest.o ${GTEST}/make/gtest_main.a

clean:
	rm MoneyTest.o
