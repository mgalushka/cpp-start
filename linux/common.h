#ifndef	_MG_CUSTOM_
#define	_MG_CUSTOM_

#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE 700

#include <sys/types.h>		/* some systems still require this */
#include <sys/stat.h>
#include <sys/termios.h>	/* for winsize */
#if defined(MACOS) || !defined(TIOCGWINSZ)
#include <sys/ioctl.h>
#endif

#include <stdio.h>		/* for convenience */
#include <stdlib.h>		/* for convenience */
#include <stddef.h>		/* for offsetof */
#include <string.h>		/* for convenience */
#include <unistd.h>		/* for convenience */
#include <signal.h>		/* for SIG_ERR */

#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>

#define TRUE    1
#define FALSE   0

#define DEBUG if(TRUE)

#define	MAXLINE	4096			/* max line length */


/*
 * Default buffer size for socket operations
 */
#define BUF_SIZE  1024

/*
 * Default file access permissions for new files.
 */
#define	FILE_MODE	(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

/*
 * Default permissions for new directories.
 */
#define	DIR_MODE	(FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)

typedef	void	Sigfunc(int);	/* for signal handlers */

#define	min(a,b)	((a) < (b) ? (a) : (b))
#define	max(a,b)	((a) > (b) ? (a) : (b))

void err_sys(const char* x) {
    perror(x);
    exit(1);
}

ssize_t socket_send(int sockfd, void *buffer, size_t len, int flag) {
  ssize_t sent_total = 0;
  int count = 0;
  int max_to_send = 1024;
  for (int sent_now = 0; sent_total != len; sent_total += sent_now) {
    int to_send = len - sent_total;
    if (to_send > max_to_send) {
      to_send = max_to_send;
    }
    sent_now = send(sockfd, buffer + sent_total, to_send, flag);
    DEBUG printf("socket_send send buffer: #%d, bytes sent in this iteration: %d.\n", count++, sent_now);
    if (sent_now == -1) break;
  }
  if (sent_total != len) {
    DEBUG printf("socket_send send requested = %zu, sent = %zu\n", len, sent_total);
  }
  return sent_total;
}

/**
 * Reading all socket data into buffer via 1024 bytes chunks
 * reallocates buffer if there is not enough size in it.
 * Buffer will contain \0 at the end of C string
 */
char * socket_recv(int sockfd, char **buffer, int flag) {
  if (!buffer) {
    return 0;
  }
  ssize_t total_read_size = 0;
  ssize_t nread = 0;
  ssize_t buffer_default_size = BUF_SIZE * sizeof(char);
  *buffer = (char *) malloc(buffer_default_size + sizeof(char));
  int iteration = 0;
  while (nread >= 0) {
    if (total_read_size > 0) {
      *buffer = (char *) realloc(*buffer, total_read_size + buffer_default_size + sizeof(char));
    }
    nread = recv(sockfd, *buffer + total_read_size, BUF_SIZE, flag);
    DEBUG printf("socket_recv iteration #%d, nread = %zd\n", iteration++, nread);
    total_read_size += nread;
    DEBUG printf(
      "Read %ld bytes from socket.\nTotal bytes read so far: %ld.\n",
      nread,
      total_read_size
    );
    DEBUG printf("socket_recv buffer (%lu): %s\n\n\n", strlen(*buffer), *buffer);

    // TODO: this is hack.
    // In real server we need to implement some kind of a END MESSAGE
    // symbol to tell server to stop reading
    if (nread < BUF_SIZE) {
      break;
    }
  }

  char *str_result = (char *) malloc(total_read_size + sizeof(char));
  strncpy(str_result, *buffer, total_read_size);
  str_result[total_read_size] = '\0';
  DEBUG printf("End of socket_recv iteration, total_read_size = %ld\n", total_read_size);
  DEBUG printf("socket_recv string output result (%lu): %s\n\n\n", strlen(str_result), str_result);

  return str_result;
}

#endif
