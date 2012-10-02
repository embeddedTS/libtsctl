#ifndef __SJA1000CAN_h
#define __SJA1000CAN_h
#include "Bus.h"
#include "Pin.h"
#include "CAN.h"
#include "Time.h"

typedef struct SJA1000CAN SJA1000CAN;

struct CANConn {
  int socket;
  unsigned char txq[sizeof(CANMessage)];
  unsigned txtail; // init=0
  unsigned char rxq[sizeof(CANMessage)];
  unsigned rxtail; // init=0
};
typedef struct CANConn CANConn;
#define BUFLEN sizeof(CANMessage)*32
struct CANData {
  // Transmit Queue:
  unsigned char txq[BUFLEN];
  unsigned txhead,txtail;
  // Receive Queue:
  unsigned char rxq[BUFLEN];
  unsigned rxtail;
  // Connections:
  CANConn *conn;
  unsigned maxconn,nconn,txc; // init=?,1,0
  // txc is the next connection to read from
  fd_set r1,r2,w1;
  // r1 contains listen, irq
  // must be initialized. by caller?
  // r2 contains listen, irq, and all CANConn sockets
  // must also be initialized (by caller?) but when we accept
  // new connections we must add the socket and when a connection
  // dies we must remove it.
  int fdmax;
  int irqfd,listen;
};
typedef struct CANData CANData;

struct SJA1000CAN {
  CAN;
  int status;
  Bus *bus;
  Pin *pin;
  int txto,baud;
  int txrdy; /// obsolete???
  CANData D;
  Time *time;
  int *baudparms;
  volatile int doabort;
  // BaudParm
};

void *SJA1000CANInit(SJA1000CAN *,void *bus,void *pin,void *time);
void SJA1000CANFini(SJA1000CAN *);
int SJA1000CANRx(SJA1000CAN *,CANMessage [1]);
int SJA1000CANTx(SJA1000CAN *,unsigned flags,unsigned id,const char* data);
unsigned SJA1000CANBaudSet(SJA1000CAN *,unsigned opt_baud);
unsigned SJA1000CANBaudGet(SJA1000CAN *);
void SJA1000CANAbort(SJA1000CAN *);
int SJA1000CANRxMulti(SJA1000CAN *,CANMessage*,int min);
void *CANStart(void *arg);
void CANStop();

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
