#include "common.h"

#if !defined(MSG_DONTWAIT)
#define	MSG_DONTWAIT	0x80
#endif

int main(int argc, char const *argv[]) {
  if (argc != 5) {
    puts("usage: client --host [HOST] --port [PORT]");
    exit(1);
  }
  char* host = NULL;
  int port = 0;

  for (int i = 0; i < argc; i++) {
    if (strncmp(argv[i], "--host", 6) == 0) {
      host = malloc(strlen(argv[i]) * sizeof(char));
      strcpy(host, argv[i+1]);
    }
    if (strncmp(argv[i], "--port", 6) == 0) {
      port = atoi(argv[i+1]);
    }
  }

  printf("Connecting to server %s:%d\n", host, port);

	int sock = 0;
	struct sockaddr_in serv_addr;

  // 1025 x 0
	char *hello = "00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000";

	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("\n Socket creation error \n");
		return -1;
	}

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);

	// Convert IPv4 and IPv6 addresses from text to binary form
	if(inet_pton(AF_INET, host, &serv_addr.sin_addr) <= 0) {
		printf("\nInvalid address/ Address not supported \n");
		return -1;
	}

  free(host);

	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
		printf("\nConnection Failed \n");
		return -1;
	}

	socket_send(sock, (void *)hello, strlen(hello), 0);
	printf("Hello message sent\n");

  // Read
  char *buffer2 = NULL;
  ssize_t total_read_size = socket_recv(sock, &buffer2, 0);
  if (total_read_size > 0) {
    printf("Message received by client (%ld): %s\n", strlen(buffer2), buffer2);
  }

	return 0;
}
