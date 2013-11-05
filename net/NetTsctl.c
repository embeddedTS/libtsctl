#include "NetTsctl.h"

tsctl *TsctlClient(char *host,int mode) {
  int socket;
  tsctl *ret;
  socket = ClientSocketNew(host,5001);
  if (socket < 0) {
    return 0;
  }
  ret = malloc(sizeof(tsctl));
  memset(ret->exception,0,sizeof(jmp_buf));
  ret->st = DescriptorStreamInit2(socket,socket,1436);
  ret->mode = mode;
  ret->count = 0;
  return ret;
}

tsctl *TsctlClient2(Stream *st,int mode) {
  tsctl *ret;
  ret = malloc(sizeof(tsctl));
  memset(ret->exception,0,sizeof(jmp_buf));
  ret->st = st;
  ret->mode = mode;
  ret->count = 0;
  return ret;
}
