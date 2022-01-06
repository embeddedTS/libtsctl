#ifndef __SJA1000CAN_h
#define __SJA1000CAN_h
#include "Bus.h"
#include "Pin.h"
#include "Time.h"
#include "CAN.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct CANConn CANConn;
typedef struct CANData CANData;
typedef struct SJA1000CAN SJA1000CAN;
struct CANConn {
  int socket;
  unsigned char txq[sizeof(CANMessage)];
  unsigned txtail;
  unsigned char rxq[sizeof(CANMessage)];
  unsigned rxtail;
};

#ifndef BUFLEN
#define BUFLEN sizeof(CANMessage)*32
#endif
struct CANData {
  unsigned char txq[BUFLEN];
  unsigned txhead;
  unsigned txtail;
  unsigned char rxq[BUFLEN];
  unsigned rxtail;
  CANConn *conn;
  unsigned maxconn;
  unsigned nconn;
  unsigned txc;
  fd_set r1;
  fd_set r2;
  fd_set w1;
  int fdmax;
  int irqfd;
  int listen;
};

struct SJA1000CAN {
	void *FUNC(Init)(SJA1000CAN *me,void *bus,void *pin,void *time);
	void FUNC(Fini)(SJA1000CAN *me);
	CANResult FUNC(Rx)(SJA1000CAN *me,CANMessage message[1]);
	CANResult FUNC(Tx)(SJA1000CAN *me,unsigned flags,unsigned id,const char *data);
	unsigned FUNC(BaudSet)(SJA1000CAN *me,unsigned opt_baud);
	unsigned FUNC(BaudGet)(SJA1000CAN *me);
	void FUNC(Abort)(SJA1000CAN *me);
	CANResult FUNC(RxMulti)(SJA1000CAN *me,CANMessage *msg,int min);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	int irq;
	int CAN_TX;
	int CAN_RX;
	int status;
	Bus *bus;
	Pin *pin;
	int txto;
	int baud;
	int txrdy;
	CANData D;
	Time *time;
	int *baudparms;
	volatile int doabort;
};

void *SJA1000CANInit(SJA1000CAN* ob,void *bus,void *pin,void *time);
void SJA1000CANFini(SJA1000CAN* ob);
CANResult SJA1000CANRx(SJA1000CAN* ob,CANMessage message[1]);
CANResult SJA1000CANTx(SJA1000CAN* ob,unsigned flags,unsigned id,const char *data);
unsigned SJA1000CANBaudSet(SJA1000CAN* ob,unsigned opt_baud);
unsigned SJA1000CANBaudGet(SJA1000CAN* ob);
void SJA1000CANAbort(SJA1000CAN* ob);
CANResult SJA1000CANRxMulti(SJA1000CAN* ob,CANMessage *msg,int min);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
