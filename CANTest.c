#define POLYGLOT_AUTO_COMPILE \
  gcc -g -fms-extensions -o CANTest CANTest.c ; exit

#include "libtsctl.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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
  int i,n,ret=0,max=0;
  struct timeval tv;

  tv.tv_sec = uswait / 1000000;
  tv.tv_usec = uswait % 1000000;
  FD_ZERO(&fdset);
  for (i=0;i<ArrayLength(fds);i++) {
    FD_SET(fds[i],&fdset);
    if (fds[i] > max) max = fds[i];
  }
  ret = select(max+1,&fdset,0,0,&tv);
  //printf("ready:");
  for (i=0;i<ArrayLength(fds);i++) {
    ready[i] = FD_ISSET(fds[i],&fdset) ? 1 : 0;
    //if (FD_ISSET(fds[i],&fdset)) printf("%d ",fds[i]);
  }
  //printf("\n");
  return ret;
}

int drain_fds(NetCANctl* *can,const int* fds) {
  int i,n=0;
  int* ready = ArrayAlloc(ArrayLength(fds),sizeof(int));
  CANMessage msg;

  check_fds(fds,ready,0);
  for (i=0;i<ArrayLength(fds);i++) {
    if (ready[i]) {
      n++;
      can[i]->Rx(can[i],&msg);
    }
  }
  return n;
}

char *getinst(char *host,int *inst) {
  char *colon = strchr(host,':');

  if (!colon) {
    *inst = 0;
    return host;
  }
  *colon = 0;
  colon++;
  *inst = strtol(colon,0,0);
  return host;
}

void dump(char* arr) {
  int i;

  for (i=0;i<ArrayLength(arr);i++) {
    printf("%02X ",arr[i]);
  }
  printf("\n");
}

int main(int argc,char *argv[]) {
  int h,i,j,k,x;
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
    char *str;
    int inst;

    str = getinst(argv[i],&inst);
    can[i-1] = (NetCANctl *)Net_CANctlInit(inst,str);
    if (!can[i-1]) {
      fprintf(stderr,"can't connect to canctl server %s\n",argv[i]);
      return 1;
    } else {
      //printf("ok %s\n",argv[i]);
      fds[i-1] = can[i-1]->socket;
      //printf("%s=%d\n",argv[i],fds[i-1]);
    }
  }


  // Part 3:
  // set the baud rate 
  for (i=1;i<argc;i++) {
    can[i-1]->BaudSet(can[i-1],100000);
  }

  // drain off anything already received
  usleep(20000);
  while (drain_fds(can,fds));

  // Part 4:
  // send a CAN frame
  int n;
  CANMessage msg;
  
  for (i=0;i<8;i++) data[i] = i;

  
  for (h=0;h<1000000;h++) {
    fprintf(stderr,"\r%d   ",h);
    for (i=0;i<argc-1;i++) {
      usleep(10000);
      data[7] = i;
      //printf("\nTx %d:",i); fflush(stdout);
      n = can[i]->Tx(can[i],FLAG_EXT_ID,0x1234,data);

      retries = 100;
      do {
	usleep(10000);
	n = check_fds(fds,ready,0);
      } while (n < argc-2 && --retries);

      if (n < argc-2) {
	for (j=0;j<argc-1;j++) {
	  if (i!=j && !ready[j]) fprintf(stderr,"%s ",argv[j+1]);
	}
	fprintf(stderr,"timeout\n");
	return 1;
      }
      //printf("%d rx\n",n);
      //return 1;
      
      for (j=0;j<argc-1;j++) {
	if (i == j) continue;
	//printf("%d",j);
	x = can[j]->Rx(can[j],&msg);
	if (x > 0) {
	  for (k=0;k<8;k++) if (msg.data[k] != data[k]) break;
	  if (k < 8) {
	    fprintf(stderr,"Rx %d data mismatch:\ngot:",j);
	    for (k=0;k<8;k++) {
	      fprintf(stderr,"%02X ",msg.data[k]);
	    }
	    fprintf(stderr,"\nnot:");
	    for (k=0;k<8;k++) {
	      fprintf(stderr,"%02X ",data[k]);
	    }
	    fprintf(stderr,"\n");
	  }
	} else {
	  printf("Error %d receiving\n",i);
	}
      }
    }
  }
  return 0;
}

// to compile on the PC:
// gcc -g -fms-extensions -o CANTest CANTest.c  
