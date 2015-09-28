all: hello.out

hello.out: hello.o
	 g++ -g -o hello.out hello.o

hello.o: hello.c
	 g++ -c hello.c
     
clean:
	 rm hello.o hello.out
