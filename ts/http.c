#include <stdio.h>
#include "Thread.h"
#include "shell.c"

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

#include "../Stream.h"

void *httpServerConstor(int socket) {
  if (socket < 0) return 0;
  return DescriptorStreamInit(socket,socket);
}

void httpServerDester(void *arg) {
  Thread *th = arg;
  Stream *st = th->data;

  st->Fini(st);
  close(th->socket);
  th->socket = -1;
}

void *httpServer(void *arg) {
  Thread *th = arg;
  int socket = th->socket;
  int i,ret=0,last,next,cmdcount=0;
  char *cstr,cmd[1024],tmp[256],*s;
  time_t t;
  Stream *st = th->data;
 
  if (!st) goto httpServerDone;

  // Assume POST, as that is all we support
  // ignore headers, because the format of our data and return is fixed
  // look for POST data, which follows headers.
  do {
    last = st->ReadChar(st);
  } while (st->InputReady(st) && last != '\r');
  while (st->InputReady(st)) {
    next = st->ReadChar(st);
    if (next == '\r') continue;
    if (last == '\n' && next == '\n') break;
    last = next;
  }
  t = time(0);
  WriteASCIIZ(st,"HTTP/1.1 200 OK\r\nExpires: Sun, 1 Apr 2012 00:00:00 GMT\r\nServer: tsctl\r\nAccess-Control-Allow-Origin: *\r\nContent-Type: text/plain; charset=UTF-8\r\nConnection: close\r\n\r\n{");

  while (st->InputReady(st)) {
    tsctl_shell(st,st);
  }
  WriteASCIIZ(st,"\"end\":1\n}");

 httpServerDone:
  //fprintf(stderr,"httpServer @%p/%d finished on socket %d\n",th,th->pid,socket);
  return 0;
}
