#ifndef __NetCAN_H
#define __NetCAN_H
#include "CAN.h"

typedef struct NetCAN NetCAN;

struct NetCAN {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  CANResult FUNC(Rx)(void *me,CANMessage message[1]);
  CANResult FUNC(Tx)(void *me,unsigned flags,unsigned id,const char *data);
  unsigned FUNC(BaudSet)(void *me,unsigned opt_baud);
  unsigned FUNC(BaudGet)(void *me);
  void FUNC(Abort)(void *me);
  CANResult FUNC(RxMulti)(void *me,CANMessage *msg,int min);
  int InitStatus;
  unsigned LockBase;
  int deferlock;
  int irq;
  int CAN_TX;
  int CAN_RX;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetCANInit(tsctl *,int instance);
void *NetCANFini(NetCAN *);
CANResult NetCANRx(NetCAN *ob,CANMessage message[1]);
CANResult NetCANTx(NetCAN *ob,uint32 flags,uint32 id,const int8* data);
uint32 NetCANBaudSet(NetCAN *ob,uint32 opt_baud);
uint32 NetCANBaudGet(NetCAN *ob);
void NetCANAbort(NetCAN *ob);
CANResult NetCANRxMulti(NetCAN *ob,CANMessage* msg,int32 min);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
