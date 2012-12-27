#ifndef __NetSPI_H
#define __NetSPI_H
#include "Net2.h"
#include "Stream.h"
#include "SPI.h"

typedef struct NetSPI NetSPI;

struct NetSPI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  SPIResult FUNC(Write)(void *me,int adrs,const unsigned char *buf);
  SPIResult FUNC(Read)(void *me,int adrs,unsigned char *buf);
  SPIResult FUNC(ReadWrite)(void *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
  SPIResult FUNC(ClockSet)(void *me,unsigned hz);
  SPIResult FUNC(EdgeSet)(void *me,int posedge);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetSPIInit(tsctl *,int instance);
void *NetSPIFini(NetSPI *);
int32 NetSPILock(NetSPI *ob,uint32 num,int32 flags);
int32 NetSPIUnlock(NetSPI *ob,uint32 num,int32 flags);
int32 NetSPIPreempt(NetSPI *ob);
SPIResult NetSPIWrite(NetSPI *ob,int32 adrs,const uint8* buf);
SPIResult NetSPIRead(NetSPI *ob,int32 adrs,uint8* buf);
SPIResult NetSPIReadWrite(NetSPI *ob,int32 adrs,const uint8* wbuf,uint8* rbuf);
SPIResult NetSPIClockSet(NetSPI *ob,uint32 hz);
SPIResult NetSPIEdgeSet(NetSPI *ob,int32 posedge);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
