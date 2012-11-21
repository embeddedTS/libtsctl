#ifndef __CAN_h
#define __CAN_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct CANMessage CANMessage;
typedef struct CAN CAN;
struct CANMessage {
  unsigned flags;
  unsigned id;
  unsigned t_sec;
  unsigned t_usec;
  unsigned length;
  unsigned char data[8];
};

typedef enum CANEvent{
  CANEventBusError=128,CANEventArbLost=64,CANEventErrorPassive=32,CANEventWakeUp=16,CANEventDataOverrun=8,CANEventErrorWarning=4,CANEventTransmitDone=2,CANEventReceiveReady=1
}CANEvent;

typedef enum CANFlags{
  FLAG_BUS_ERROR=1,FLAG_ERROR_PASSIVE=2,FLAG_DATA_OVERRUN=4,FLAG_ERROR_WARNING=8,FLAG_RTR=16,FLAG_EXT_ID=32,FLAG_LOCAL=64,FLAG_CONTROL=128
}CANFlags;

enum {
	NetCAN_Rx=0,
	NetCAN_Tx=1,
	NetCAN_BaudSet=2,
	NetCAN_BaudGet=3,
	NetCAN_Abort=4,
	NetCAN_RxMulti=5,
	XCAN_APICount=6
};
struct CAN {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Rx)(void *me,CANMessage [1]);
	int FUNC(Tx)(void *me,unsigned flags,unsigned id,const char *data);
	unsigned FUNC(BaudSet)(void *me,unsigned opt_baud);
	unsigned FUNC(BaudGet)(void *me);
	void FUNC(Abort)(void *me);
	int FUNC(RxMulti)(void *me,CANMessage *msg,int min);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	int irq;
	int CAN_TX;
	int CAN_RX;
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
