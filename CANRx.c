#define THREAD_USE_POSIX
#include "libtsctl.h"
#include <stdlib.h>
#include <stdio.h>

void CANMessagePrint(CANMessage *msg) {
  struct tm * tm;
  int i;

  if (msg->flags & FLAG_CONTROL) printf("*** control packet\n");
  if (msg->flags & FLAG_BUS_ERROR) printf("*** bus error\n");
  if (msg->flags & FLAG_ERROR_PASSIVE) printf("*** error passive\n");
  if (msg->flags & FLAG_DATA_OVERRUN) printf("*** data overrun error\n");
  if (msg->flags & FLAG_ERROR_WARNING) printf("*** error warning\n");
  tm = localtime((time_t *)&msg->t_sec);
  printf("%02d:%02d:%02d.%06d %c%c ", 
	 tm->tm_hour, tm->tm_min, tm->tm_sec,msg->t_usec, 
	 (msg->flags & FLAG_EXT_ID) ? 'E' : 'S', 
	 (msg->flags & FLAG_RTR)     ? 'R' : '.');
  if (msg->flags & FLAG_CONTROL) {
    printf("id=0x%08x ", msg->id);
    printf("cmd=%d ",msg->length);
    printf("dat=");
    for (i = 0; i < 8 ; i++) {
      printf("0x%02x", msg->data[i]);
      if (i != (msg->length - 1)) printf(":");
    }
  } else if (msg->length != 0) {
    printf("id=0x%08x ", msg->id);
    if (msg->length < 0 || msg->length > 8) {
      printf("bad length=%d\n",msg->length);
    } else {
      printf("dat=");
      for (i = 0; i < msg->length; i++) {
	printf("0x%02x", msg->data[i]);
	if (i != (msg->length - 1)) printf(":");
      }
    }
  }
  printf("\n");
}

CAN *can;

static void alarmsig(int x) {
  can->Abort(can);
}

int main(int argc,char *argv[]) {
  int i;
  CANMessage msg;

  can = CANInit(0);
  if (!can) {
    fprintf(stderr,"Error: No CAN present\n");
    return 1;
  }
  if (SignalCapture(2,alarmsig) < 0) {
    fprintf(stderr,"signal capture error:%m\n");
    return 1;
  }
  can->BaudSet(can,1000000);
  printf("Waiting to Rx\n");
  i = can->Rx(can,&msg);
  if (i > 0) {
    CANMessagePrint(&msg);
  } else {
    printf("Error %d receiving\n",i);
  }
  return 0;
}
