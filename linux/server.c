#include "common.h"
#include <sys/socket.h>
#include <netinet/in.h> 

#define TRUE 1

int main(int argc, char const *argv[]) { 
  
  if (argc != 3) {
    puts("usage: server --port [PORT]");
    exit(1);
  }
  int port = atoi(argv[2]);
  
	int server_fd, new_socket, valread; 
	
	// Creating socket file descriptor 
	if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) { 
		perror("socket failed"); 
		exit(EXIT_FAILURE); 
	}
  
  struct sockaddr_in address; 
	int opt = 1; 
	int addrlen = sizeof(address); 
	char buffer[1024] = {0}; 
	char *hello = "Hello from server";  
	
	if (setsockopt(
      server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)
    )) { 
		perror("setsockopt"); 
		exit(EXIT_FAILURE); 
	} 
	address.sin_family = AF_INET; 
	address.sin_addr.s_addr = INADDR_ANY; 
	address.sin_port = htons( port ); 
	
	// Attaching socket 
	if (bind(
      server_fd, (struct sockaddr *)&address, sizeof(address))<0
    ) { 
		perror("bind failed"); 
		exit(EXIT_FAILURE); 
	} 
	if (listen(server_fd, 3) < 0) { 
		perror("listen"); 
		exit(EXIT_FAILURE); 
	} 
	if ((new_socket = accept(server_fd, (struct sockaddr *)&address, 
					(socklen_t*)&addrlen)) < 0) { 
		perror("accept"); 
		exit(EXIT_FAILURE); 
	} 
  while (TRUE) {
    valread = read(new_socket, buffer, 1024); 
    printf("%s\n", buffer); 
    
    char *separator = " >> ";
    int totalLength = strlen(buffer) + strlen(separator) + strlen(hello);
    char *new_message = (char *) malloc(totalLength * sizeof(char));
    strcat(new_message, hello);
    strcat(new_message, separator);
    strcat(new_message, buffer);
    send(new_socket, new_message, strlen(new_message), 0); 
    printf("Hello message sent\n"); 
  }
	return 0; 
} 
