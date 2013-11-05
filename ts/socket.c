#ifndef __socket_c
#define __socket_c
#include <sys/types.h>		/* standard system types       */
#include <netinet/in.h>		/* Internet address structures */
#include <sys/socket.h>		/* socket interface functions  */
#include <netdb.h>		/* host to IP resolution       */
#include <string.h>
#include <netinet/tcp.h>        // TCP_NODELAY
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "nosig.h"

static inline int FileBlockingSet(int fd,int on) {
  return fcntl(fd, F_SETFL, on ? 0 : (O_NDELAY | O_NONBLOCK));
}


int ServerSocketNew(int port) {
  int			rc;       /* system calls return value storage  */
  int			s;        /* socket descriptor                  */
  int			cs;       /* new connection's socket descriptor */
  struct sockaddr_in	sa;       /* Internet address struct            */
  int x = 1;

  memset(&sa, 0, sizeof(sa));
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = INADDR_ANY;
  
  s = socket(AF_INET, SOCK_STREAM, 0);
  if (s < 0) {
    //perror("socket: allocation failed");
    return -1;
  }
  setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &x, 4);
  if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &x, 4) < 0) {
    perror("TCP_NO_DELAY");
    exit(1);
  }
  if (FileBlockingSet(s,0) < 0) {
    printf("ERROR: Unable to set server socket non-blocking (%m)!\n");
    NOSIG(close(s));
    return -1;
  }
  rc = bind(s, (struct sockaddr *)&sa, sizeof(sa));
  if (rc) {
    //perror("bind");
    return -1;
  }
  rc = listen(s, 5);
  if (rc) {
    //perror("listen");
    return -1;
  }  
  return s;
}

int ClientSocketNew(char *host,int port) {
  int			rc;            /* system calls return value storage */
  int            	x,s;             /* socket descriptor */
  struct addrinfo *result,*rp;
  struct addrinfo hints;
  char service[8];

  sprintf(service,"%d",port);
  memset(&hints,0,sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  // next line commented out because when compiling for TS-4500 I get this:
  // error: `AI_NUMERICSERV' undeclared
  //hints.ai_flags = AI_NUMERICSERV;
  if (getaddrinfo(host,service,&hints,&result) < 0) {
    return -1;
  }
  for (rp=result; rp != NULL; rp = rp->ai_next) {
    s = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
    if (s < 0) continue;
    if (setsockopt(s, IPPROTO_TCP, TCP_NODELAY, &x, 4) < 0) {
      perror("TCP_NO_DELAY");
    }
    if (connect(s, rp->ai_addr, rp->ai_addrlen) != -1) break;
    close(s);
  }
  if (rp == NULL) return -1;
  freeaddrinfo(result);
  return s;
}

#endif
