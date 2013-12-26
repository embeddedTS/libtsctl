#include <stdlib.h>
#include <stdio.h>
#include "libtsctl.h"

CAN *can;

static void alarmsig(int x) {
  can->Abort(can);
}

int main(int argc,char *argv[]) {
  Bus *bus;
  int i;
  ArrayAuto(char,data,ARR(1,2,3,4,5,6,7));

  can = CANInit(0);
  if (!can) {
    printf("No CAN object found\n");
    return 1;
  }
  if (SignalCapture(2,alarmsig) < 0) {
    fprintf(stderr,"signal capture error:%m\n");
    return 1;
  }
  can->BaudSet(can,1000000);
  can->Tx(can,0,0x234,data);
  return 0;
}
