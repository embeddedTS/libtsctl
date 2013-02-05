#include "ts/Net.h"
#include "Stream.h"

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
