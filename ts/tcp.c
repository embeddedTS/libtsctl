#include <stdio.h>
#include <sys/select.h>
#define THREAD_USE_POSIX
#include "Thread.h"
#include "socket.h"
#include "tcp.h"

// if th->socket < 0, then it's a port number
// th->data contains the ThreadFunction to call for each connection
void *ServerTCP(void *arg) {
  Thread *th = arg;
  int rc,total=0,s;
  fd_set rfd, c_rfd;
  struct sockaddr_in csa;
  unsigned size_csa = sizeof(csa);
  pthread_t th1;
  void *data;
  ServerData *sd = th->data;

  if (th->socket < 0) {
    th->socket = ServerSocketNew(-th->socket);
    if (th->socket < 0) {
      return 0;
    }
  }

  FD_ZERO(&rfd);
  FD_SET(th->socket,&rfd);

  while (1) {
    do {
      c_rfd = rfd;
      //fprintf(stderr,"waiting for connection on socket %d\n",th->socket);
      rc = select(th->socket+1, &c_rfd, 0, 0, 0);
    } while (rc == -1 && errno == EINTR);
    s = accept(th->socket, (struct sockaddr *)&csa, &size_csa);
    //fprintf(stderr,"accepted socket %d\n",s);
    if (s < 0) continue;
    data = sd->constor(s);
    ThreadNew(th->name,++total,sd->f,s,data,sd->destor);
  }
}
