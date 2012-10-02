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

typedef struct {
  OutInfo oi;
  FILE *f;
} httpServerData;

void *httpServerConstor(int socket) {
  httpServerData *data = malloc(sizeof(httpServerData));
  data->oi.ht = HashTableNewASCIIZ();
  data->oi.tsctl_o = socket;
  data->oi.fAssign = 2;
  data->oi.oMode = MODE_DEC;
  data->oi.aMode = MODE_STR;
  fcntl(socket,F_SETFL,fcntl(socket,F_GETFL,0)&~O_NONBLOCK);
  data->f = fdopen(socket,"w+");
  return data;
}

void httpServerDester(void *arg) {
  Thread *th = arg;
  httpServerData *data = th->data;

  HashTableDestroy(data->oi.ht,0);
  th->socket = -1;
  fclose(data->f);
  free(data);
}

void *httpServer(void *arg) {
  Thread *th = arg;
  int socket = th->socket;
  int i,ret=0,last,next,cmdcount=0;
  char *cstr,cmd[1024],tmp[256],*s;
  time_t t;
  httpServerData *data = th->data;
 
  //fprintf(mf,"Nexty[];\n"); fflush(mf);

  //fprintf(stderr,"httpServer @%p/%d started on socket %d\n",th,th->pid,socket);
#if 0
  {
    Thread *cur = head_thread;

    while (cur) {
      fprintf(stderr,"%p:%s.%d ",cur,cur->name,cur->instance);
      cur = cur->next;
    }
    fprintf(stderr,"\n");
  }
#endif
  if (data->f == 0) goto httpServerDone;

  // Assume POST, as that is all we support
  // ignore headers, because the format of our data and return is fixed
  // look for POST data, which follows headers.
  do {
    last = fgetc(data->f);
  } while (!feof(data->f) && last != '\r');
  while (!feof(data->f)) {
    next = fgetc(data->f);
    if (next == '\r') continue;
    if (last == '\n' && next == '\n') break;
    last = next;
  }
  t = time(0);
  //fprintf(stderr,"httpServer %d/%d sending header\n",socket,th->pid);
  sprintf(cmd,"HTTP/1.1 200 OK\r\nExpires: Sun, 1 Apr 2012 00:00:00 GMT\r\nServer: tsctl\r\nAccess-Control-Allow-Origin: *\r\nContent-Type: text/plain; charset=UTF-8\r\nConnection: close\r\n\r\n");
  write(socket,cmd,strlen(cmd));
  write(socket,"{",1);
  while (!feof(data->f)) {
    ThreadEnterBlock();
    cmd[0] = 0;
    fgets(cmd,1023,data->f);
    ThreadLeaveBlock();
    //fprintf(stderr,"httpServer %d read:%s\n",socket,cmd);
    cstr = cmd;
    while (*cstr == '\r') cstr++;
    if (*cstr == 0) continue;
    if (!strncmp(cstr,"end",3) && (cstr[3] == '\r' || cstr[3] == '\n')) break;
    //if (cmdcount++ > 0 && ret) write(socket,",",1);
    s = cstr;
    while (*s) s++; s--;
    while ((*s == '\n' || *s == '\r') && s > cstr) s--;
    s[1] = 0;

    char **argv;
    argv = split(cmd,' ');
    if (!argv) continue;
    //fprintf(stderr,"httpServer %d command:",socket);
    //for (i=0;i<ArrayLength(argv);i++) {
    //  fprintf(stderr,"%s ",argv[i]);
    //}
    //fprintf(stderr,"\n");
    ret = tsctlInterpret(&data->oi,argv);
    //fprintf(stderr,"httpServer %d command done\n");

    // TO DO: ArrayFree elements
    for (i=0;i<ArrayLength(argv);i++) {
      ArrayFree(argv[i]);
    }
    ArrayFree(argv);
  }
  write(socket,"\"end\":1\n}",9);

 httpServerDone:
  //fprintf(stderr,"httpServer @%p/%d finished on socket %d\n",th,th->pid,socket);
  return 0;
}
