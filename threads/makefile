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

all: RunThreads.o Promises.o PackagedTask.o

# -stdlib=libc++

RunThreads.o:
	${CC} -undefined dynamic_lookup -O1 -fsanitize=address -fno-omit-frame-pointer \
	-v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -stdlib=libc++ -std=c++14 \
	-L${GLOG_LIB} -lglog RunThreads.cpp \
	-o RunThreads.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}


Promises.o:
	${CC} -undefined dynamic_lookup -O1 -fsanitize=address -fno-omit-frame-pointer \
	-v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -stdlib=libc++ -std=c++14 \
	-L${GLOG_LIB} -lglog Promises.cpp \
	-o Promises.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

PackagedTask.o:
	${CC} -undefined dynamic_lookup -O1 -fsanitize=address -fno-omit-frame-pointer \
	-v -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -stdlib=libc++ -std=c++14 \
	-L${GLOG_LIB} -lglog PackagedTask.cpp \
	-o PackagedTask.o ${GTEST}/make/gtest_main.a ${FOLLY_LIB} ${DOUBLE_CONVERSION_LIB}

clean:
	rm -f RunThreads.o
	rm -f Promises.o
	rm -f PackagedTask.o
