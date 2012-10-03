#include "libtsctl.h"
#include <stdlib.h>
#include <stdio.h>
#include "ts/Array.h"

#include "ts/NetCANctl.c"
#include "ts/Net.c"
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

CAN *Net_CANctlInit(int inst,char *host){
  int socket = ClientSocketNew(host,7552+inst);
  if (socket < 0) return 0;
  NetCANctl *obj = malloc(sizeof(NetCANctl));
  memset(obj,0,sizeof(*obj));

  return NetCANctlInit(obj,socket);
}

int check_fds(const int* fds,int *ready,unsigned uswait) {
  fd_set fdset;
  int i,ret=0,max=0;
  struct timeval tv;

  tv.tv_sec = uswait / 1000000;
  tv.tv_usec = uswait % 1000000;
  FD_ZERO(&fdset);
  for (i=0;i<ArrayLength(fds);i++) {
    FD_SET(fds[i],&fdset);
    if (fds[i] > max) max = fds[i];
  }
  ret = select(max+1,&fdset,0,0,&tv);
  printf("ready:");
  for (i=0;i<ArrayLength(fds);i++) {
    ready[i] = FD_ISSET(fds[i],&fdset) ? 1 : 0;
    if (FD_ISSET(fds[i],&fdset)) printf("%d ",fds[i]);
  }
  printf("\n");
  return ret;
}

int main(int argc,char *argv[]) {
  int i,j;
  ArrayAutoOfSize(char,data,8);
  int* fds = ArrayAlloc(argc-1,sizeof(int));
  int* ready = ArrayAlloc(argc-1,sizeof(int));

  if (argc < 2) {
    printf("usage: CANTest <host> ...\n");
    return 1;
  }
  // Part 1: (TO DO) ssh to each host and start canctl if needed

  // Part 2: connect to the canctl server
  NetCANctl* *can=ArrayAlloc(argc-1,sizeof(CAN *));
  int retries=100;
  for (i=1;i<argc;i++) {
    can[i-1] = (NetCANctl *)Net_CANctlInit(0,argv[i]);
    if (!can[i-1]) {
      fprintf(stderr,"can't connect to canctl server %s\n",argv[i]);
      return 1;
    } else {
      printf("ok %s\n",argv[i]);
      fds[i-1] = can[i-1]->socket;
      printf("%s=%d\n",argv[i],fds[i-1]);
    }
  }


  // Part 3:
  // set the baud rate 
  for (i=1;i<argc;i++) {
    can[i-1]->BaudSet(can[0],1000000);
  }
  
  // Part 4:
  // send a CAN frame
  int n;
  CANMessage msg;

  i=0;

  usleep(10000); // 
  n = can[i]->Tx(can[i],FLAG_EXT_ID,0x1234,data);
  do {
    usleep(10000);
    n = check_fds(fds,ready,0);
  } while (n < 4);
  printf("%d rx\n",n);
  return 1;

  i = can[0]->Rx(can[0],&msg);
  if (i > 0) {
    CANMessagePrint(&msg);
  } else {
    printf("Error %d receiving\n",i);
  }
  return 0;
}

// to compile on the PC:
// gcc -g -fms-extensions -o CANTest CANTest.c  
