#!/bin/bash

rm javapkg/MainLoader.class javapkg/libmainloader.jnilib

# builing java endpoint
javac javapkg/MainLoader.java

# builing library
g++ -Wall -I${JAVA_HOME}/include/darwin -I${JAVA_HOME}/include -iquote . \
 -c MainLoader.cpp

g++ -dynamiclib -o javapkg/libmainloader.jnilib MainLoader.o
rm MainLoader.o

export DYLD_LIBRARY_PATH=javapkg

# running java
java -Djava.library.path=javapkg -cp javapkg:. MainLoader
