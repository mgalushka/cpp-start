all: hello.o

hello.o: hello.obj
	g++ -Wall hello.obj -o hello.o

hello.obj: hello.cpp
	g++ -Wall -c hello.cpp -o hello.obj

clean:
	rm hello.o hello.obj
