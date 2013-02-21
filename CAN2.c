#define THREAD_USE_POSIX
#include "libtsctl.c"
#include <stdlib.h>
#include <stdio.h>
#include "Array.h"

#include "NetCANctl.c"
#include "Net.c"
CAN *Net_CANctlInit(int inst,char *host,int mode){
  int socket = ClientSocketNew(host,7552+inst);
  if (socket < 0) return 0;
  NetCANctl *obj = malloc(sizeof(NetCANctl));
  memset(obj,0,sizeof(*obj));

  return NetCANctlInit(obj,socket);
}

int main(int argc,char *argv[]) {
  // Part 1:
  // start the canctl server
  CANPort ci;

  ThreadInit();
  ci.can = CANInit(0);
  ci.port = 7552;
  ThreadNew("canctl server",0,CANStart,0,&ci,0);

  // Part 2:
  // connect to the canctl server
  CAN *can=0;
  int retries=100;
  while (!can && retries-- > 0) {
    can = Net_CANctlInit(0,"localhost",0);
  }
  if (retries < 0) {
    fprintf(stderr,"error starting canctl server\n");
    return 1;
  }
  // Part 3:
  // set the baud rate and send a CAN frame
  ArrayAuto(char,data,ARR(1,2,3,4,5,6,7));
  int n;

  can->BaudSet(can,1000000);
  n = can->Tx(can,0,0x1234,data);
  return 0;
}
