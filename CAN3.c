#include "libtsctl.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthread.h>
#include "NetCANctl.c"
#include "Net.c"

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

CAN *Net_CANctlInit(int inst,char *host,int mode){
  int socket = ClientSocketNew(host,7552+inst);
  if (socket < 0) return 0;
  NetCANctl *obj = malloc(sizeof(NetCANctl));
  memset(obj,0,sizeof(*obj));

  return NetCANctlInit(obj,socket);
}

void *task1(void *arg) {
  int i;
  for (i=0;i<100000000;i++) {
    if (i % 10000000 == 0) {
      fprintf(stderr,"x");
    }
    //sleep(1);
  }
}

int main(int argc,char *argv[]) {
  // Part 1:
  // start the canctl server
  CANPort ci;
  int mode;

  if (argc < 2) {
    printf("must specify 0 (Tx), 1 (Rx), or 2 (Rx+thread)\n");
    return 1;
  }
  mode = atoi(argv[1]);
  if (mode < 0 || mode > 2) {
    printf("invalid mode, try 0 (Tx), 1 (Rx), or 2 (Rx+thread)\n");
    return 1;
  }

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
  can->BaudSet(can,100000);
  pthread_t thread1;

  if (mode == 2) {
    mode = 1;
    if (pthread_create(&thread1, 0,task1,0) < 0) {
      perror("pthread_create");
    }
  }

  if (mode == 0) {
    ArrayAuto(char,data,ARR(1,2,3,4,5,6,7));
    int i,n;
    for (i=0;i<10;i++) {
      n = can->Tx(can,0,0x1234,data);
      if (n > 0) {
	fprintf(stderr,"t");
	sleep(1);
      } else {
	fprintf(stderr,"\nError %d\n",n);
	return 1;
      }
    }
    return 0;
  }
  if (mode == 1) {
    CANResult result;
    CANMessage msg[1];
    int i,n;

    for (i=0;i<10;i++) {
      result = can->Rx(can,msg);
      if (result > 0) {
	fprintf(stderr,"r");
      } else {
	fprintf(stderr,"\nError %d\n",result);
	return 1;
      }
    }
    return 0;
  }

  return 0;
}
