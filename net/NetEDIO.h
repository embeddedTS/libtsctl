#ifndef __NetEDIO_H
#define __NetEDIO_H
#include "NetTsctl.h"
#include "EDIO.h"

typedef struct NetEDIO NetEDIO;

struct NetEDIO {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  int *FUNC(QueryFunction)(void *me,EDIOType type);
  int FUNC(PWM)(void *me,int num,unsigned periodHigh,unsigned periodLow);
  int FUNC(QueryPWM)(void *me,int num,unsigned periodHigh[1],unsigned periodLow[1]);
  int FUNC(PWMfd)(void *me,int num,unsigned freq,unsigned DC);
  int FUNC(QueryPWMfd)(void *me,int num,unsigned freq[1],unsigned DC[1]);
  int FUNC(QuadratureCount)(void *me,int num);
  unsigned long long FUNC(EdgeCount)(void *me,int num,int edge);
  int FUNC(Glitched)(void *me,int num);
  int FUNC(HBridge)(void *me,int num,HBState state);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetEDIOInit(tsctl *,int instance);
void *NetEDIOFini(NetEDIO *);
int32 NetEDIOLock(NetEDIO *ob,uint32 num,int32 flags);
int32 NetEDIOUnlock(NetEDIO *ob,uint32 num,int32 flags);
int32 NetEDIOPreempt(NetEDIO *ob);
int32* NetEDIOQueryFunction(NetEDIO *ob,EDIOType type);
int32 NetEDIOPWM(NetEDIO *ob,int32 num,uint32 periodHigh,uint32 periodLow);
int32 NetEDIOQueryPWM(NetEDIO *ob,int32 num,uint32 periodHigh[1],uint32 periodLow[1]);
int32 NetEDIOPWMfd(NetEDIO *ob,int32 num,uint32 freq,uint32 DC);
int32 NetEDIOQueryPWMfd(NetEDIO *ob,int32 num,uint32 freq[1],uint32 DC[1]);
int32 NetEDIOQuadratureCount(NetEDIO *ob,int32 num);
uint32 NetEDIOEdgeCount(NetEDIO *ob,int32 num,int32 edge);
int32 NetEDIOGlitched(NetEDIO *ob,int32 num);
int32 NetEDIOHBridge(NetEDIO *ob,int32 num,HBState state);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
