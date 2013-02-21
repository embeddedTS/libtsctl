#include <stdlib.h>
#include <stdio.h>
#include "libtsctl.c"

void CANMessagePrint(CANMessage *msg) {
  struct tm * tm;
  int i;

  if (msg->flags & FLAG_CONTROL) printf("*** control packet\n");
  if (msg->flags & FLAG_BUS_ERROR) printf("*** bus error\n");
  if (msg->flags & FLAG_ERROR_PASSIVE) printf("*** error passive\n");
  if (msg->flags & FLAG_DATA_OVERRUN) printf("*** data overrun error\n");
  if (msg->flags & FLAG_ERROR_WARNING) printf("*** error warning\n");
  tm = localtime(&msg->timestamp.tv_sec);
  printf("%02d:%02d:%02d.%06d %c%c ", 
	 tm->tm_hour, tm->tm_min, tm->tm_sec,msg->timestamp.tv_usec, 
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

typedef struct {
  CAN *can;
  CANMessage msg;
} CANThreadStruct;

void *can_receive (void *cts) {
  int i;
  CAN *can = ((CANThreadStruct*)cts)->can;
  CANMessage *msg = &(((CANThreadStruct*)cts)->msg);
  printf("Vor Rx!\n");
  fflush(stdout);
  i = can->Rx(can,msg);
  i > 0 ? CANMessagePrint(msg) : printf("Error %d receiving\n",i);
  fflush(stdout);
}

int can_receive_thread(CANThreadStruct *cts) {
  pthread_t p_receive;

  pthread_create (&p_receive, NULL, can_receive, (void*)cts);
  sleep(2);
  if (!pthread_kill(p_receive,0)) { // 0..is running
    // Abort Receive
    cts->can->Abort;
    return 1;
  }
  return 0;
}

int main(int argc,char *argv[]) {
  CAN *can;
  int i;
  CANMessage msg;

  can = CANInit(0);
  can->BaudSet(can,1000000);
  i = can->Rx(can,&msg);
  if (i > 0) {
    CANMessagePrint(&msg);
  } else {
    printf("Error %d receiving\n",i);
  }
  return 0;
}
