#ifndef __SJA1000CAN_h
#define __SJA1000CAN_h
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
	int FUNC(Rx)(SJA1000CAN *me,CANMessage [1]);
	int FUNC(Tx)(SJA1000CAN *me,unsigned flags,unsigned id,const char *data);
	unsigned FUNC(BaudSet)(SJA1000CAN *me,unsigned opt_baud);
	unsigned FUNC(BaudGet)(SJA1000CAN *me);
	void FUNC(Abort)(SJA1000CAN *me);
	int FUNC(RxMulti)(SJA1000CAN *me,CANMessage *,int min);
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
int SJA1000CANRx(SJA1000CAN* ob,CANMessage [1]);
int SJA1000CANTx(SJA1000CAN* ob,unsigned flags,unsigned id,const char *data);
unsigned SJA1000CANBaudSet(SJA1000CAN* ob,unsigned opt_baud);
unsigned SJA1000CANBaudGet(SJA1000CAN* ob);
void SJA1000CANAbort(SJA1000CAN* ob);
int SJA1000CANRxMulti(SJA1000CAN* ob,CANMessage *,int min);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
