#ifndef __socket_h
#define __socket_h
#include <sys/types.h>		/* standard system types       */
#include <netinet/in.h>		/* Internet address structures */
#include <sys/socket.h>		/* socket interface functions  */
#include <netdb.h>		/* host to IP resolution       */
#include <string.h>
#include <netinet/tcp.h>        // TCP_NODELAY
#include <fcntl.h>

#include "nosig.h"

static inline int FileBlockingSet(int fd,int on) {
  return fcntl(fd, F_SETFL, on ? 0 : (O_NDELAY | O_NONBLOCK));
}


int ServerSocketNew(int port);
int ClientSocketNew(char *host,int port);
#endif
