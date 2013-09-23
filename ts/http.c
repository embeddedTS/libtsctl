#include <stdio.h>
#include "Thread.h"
#include "shell.h"
#include "HashTable.h"
#include "Stream.h"

/*
typedef struct OutInfo OutInfo;

typedef enum {
  MODE_HEX = 16,
  MODE_DEC = 10,
  MODE_OCT = 8,
  MODE_STR = 0
} OutputMode;

struct OutInfo {
  HashTable *ht;
  int tsctl_o;
  int fAssign;
  OutputMode oMode,aMode;
};

int tsctlInterpret(OutInfo *oi,char** argv);
extern Thread *head_thread;
*/

void *httpServerConstor(int socket) {
  if (socket < 0) return 0;
  return DescriptorStreamInit2(socket,socket,1436);
}

void httpServerDester(void *arg) {
  Thread *th = arg;
  Stream *st = th->data;

  st->Fini(st);
  close(th->socket);
  th->socket = -1;
}

static inline unsigned long long TimeDifference(struct timeval t0,struct timeval t1) {
  return (t1.tv_usec - t0.tv_usec) + 1000000 * (t1.tv_sec - t0.tv_sec);
}

void calcdt(struct timeval t0,struct timeval t1,int *dts,int *dtus) {
  unsigned long long dtus1 = TimeDifference(t0,t1);
  *dts = dtus1/1000000;
  *dtus = dtus1%1000000;
}

void *httpServer(void *arg) {
  Thread *th = arg;
  int socket = th->socket;
  int i,ret=0,last,next,dts,dtus;
  char *cstr,*s;
  Stream *st = th->data;
  struct timeval t0,t1,t2;
 
  if (!st) goto httpServerDone;
  gettimeofday(&t0,0);

  // Assume POST, as that is all we support
  // ignore headers, because the format of our data and return is fixed
  // look for POST data, which follows headers.
  do {
    last = st->ReadChar(st);
  } while (last > 0 && last != '\r');
  if (last <= 0) return 0;
  while (1) {
    next = st->ReadChar(st);
    if (next <= 0) return 0;
    if (next == '\r') continue;
    if (last == '\n' && next == '\n') break;
    last = next;
  }
  //t = time(0);
  WriteASCIIZ(st,"HTTP/1.1 200 OK\r\nExpires: Sun, 1 Apr 2012 00:00:00 GMT\r\nServer: tsctl\r\nAccess-Control-Allow-Origin: *\r\nContent-Type: text/plain; charset=UTF-8\r\nConnection: close\r\n\r\n{");
  st->Flush(st);
  while (!st->isEOF(st)) {
    if (tsctl_shell(st,st)) break;
    st->Flush(st);
  }
  gettimeofday(&t1,0);
  calcdt(t0,t1,&dts,&dtus);
  WriteF(st,"\"t0\" : %d.%06d,\n",t0.tv_sec,t0.tv_usec);
  WriteF(st,"\"t1\" : %d.%06d,\n",t1.tv_sec,t1.tv_usec);
  WriteF(st,"\"t\" : %d.%06d,\n",dts,dtus);            
  WriteASCIIZ(st,"\"end\":1\n}");
  st->Flush(st);
 httpServerDone:
  //fprintf(stderr,"httpServer @%p/%d finished on socket %d\n",th,th->pid,socket);
  return 0;
}
