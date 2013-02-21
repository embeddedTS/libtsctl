#include "libtsctl.c"
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

int check_fd(int fd,unsigned uswait) {
  fd_set fds;
  int ret;
  struct timeval tv;

  tv.tv_sec = uswait / 1000000;
  tv.tv_usec = uswait % 1000000;

  FD_ZERO(&fds);
  FD_SET(fd,&fds);
  ret = select(fd+1,&fds,0,0,&tv);
  return ret;
}

int SJA1000CANDetect(SJA1000CAN *can);

int main(int argc,char *argv[]) {
  int i,j,irqfd;
  CANMessage msg;
  ArrayAuto(char,data,ARR(1,2,3,4,5,6,7,8));
  System *sys;
  Bus *bus;

  can = CANInit(0);
  if (!can) {
    fprintf(stderr,"No CAN object found\n");
    return 1;
  }
  printf("CAN detect returns %d\n",SJA1000CANDetect((SJA1000CAN *)can));

  sys = SystemInit(0);
  i = sys->CANBusGet(sys,0);
  printf("CAN Bus is bus %d\n",i);
  bus = BusInit(i);

  printf("Capturing CAN IRQ %d\n",can->irq);

  {
    char tmp[80];
    sprintf(tmp,"/proc/irq/%d/irq",can->irq);
    irqfd = open(tmp,O_RDONLY|O_SYNC);
    if (irqfd < 0) {
      fprintf(stderr,"open:%m\n");
      return 1;
    }
  }
  printf("IRQ mask was %04X\n",bus->Peek8(bus,4));
  bus->Lock(bus,0,0);
  bus->Poke8(bus,4,0xFF);
  i = bus->Peek8(bus,4);
  if (i != 0xFF) {
    fprintf(stderr,"error writing IRQ mask, got %04X, expected 0xFF\n",i);
    return 1;
  }
  bus->Unlock(bus,0,0);
  do {
    bus->Lock(bus,0,0);
    i = bus->Peek8(bus,3);
    bus->Unlock(bus,0,0); 
   printf("IRQ state=%04X\n",i);
   j = check_fd(irqfd,0);
    if (j < 0) {
      fprintf(stderr,"select:%m\n");
    } else if (j == 0) {
      if (i) fprintf(stderr,"error: no interrupt pending\n");
    } else { // j > 0
      if (i) fprintf(stderr,"warning: interrupt pending\n");
      read(irqfd,&j,4);
      printf("irq condition read\n");
    }
    if (i & 1) {
      printf("getting CAN message\n",i,i&1);
      j = can->Rx(can,&msg);
      if (j > 0) {
	CANMessagePrint(&msg);
      } else {
	printf("Error %d receiving\n",j);
      }
    }
  } while (i & 1);

  if (SignalCapture(2,alarmsig) < 0) {
    fprintf(stderr,"signal capture error:%m\n");
    return 1;
  }

  printf("setting baud rate\n");
  can->BaudSet(can,1000000);
  printf("sending message\n");
  can->Tx(can,0,0x1234,data);


  // now wait to receive a message from another board, using select
  // to wait for a while for an interrupt, and then periodically checking
  // the CAN registers to make sure the interrupt didn't fail
  printf("Now waiting for another CAN message using interrupts\n");
  j = 0;
  while (1) {
    if (check_fd(irqfd,1000)) {
      break;
    }
    if (j) {
      printf("Interrupt failed to signal received message\n");
      break;
    }
    bus->Lock(bus,0,0);
    i = bus->Peek8(bus,2);
    if (i & 1) j++;
    bus->Unlock(bus,0,0); 
  }
  printf("getting CAN message\n",i,i&1);
  j = can->Rx(can,&msg);
  if (j > 0) {
    CANMessagePrint(&msg);
  } else {
    printf("Error %d receiving\n",j);
  }
  return 0;
}
