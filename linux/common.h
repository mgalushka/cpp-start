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
    DEBUG printf("Send buffer: %d, bytes sent: %d\n", count++, sent_now);
    if (sent_now == -1) break;
  }
  if (sent_total != len) {
    DEBUG printf("Send requested = %zu, sent = %zu", len, sent_total);
  }
  return sent_total;
}

ssize_t socket_recv(int sockfd, char **buffer, int flag) {
  ssize_t total_read_size = 0;
  ssize_t nread = 0;
  ssize_t buffer_default_size = BUF_SIZE * sizeof(char);

  while (nread >= 0) {
    if (buffer == NULL) {
      *buffer = (char *) malloc(buffer_default_size);
    } else {
      *buffer = (char *) realloc(*buffer, total_read_size + buffer_default_size);
    }
    nread = recv(sockfd, *buffer + total_read_size, BUF_SIZE, flag);
    total_read_size += nread;
    DEBUG printf(
      "Read %ld bytes from socket\n Total bytes read so far: %ld\n",
      nread,
      total_read_size
    );
    DEBUG printf("Buffer: %s\n", *buffer);

    // TODO: this is hack.
    // In real server we need to implement some kind of a END MESSAGE
    // symbol to tell server to stop reading
    if (nread < BUF_SIZE) {
      break;
    }
  }

  return total_read_size;
}

#endif
