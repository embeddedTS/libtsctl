#ifndef __NetPin_H
#define __NetPin_H
#include "NetTsctl.h"
#include "Pin.h"

typedef struct NetPin NetPin;

struct NetPin {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  PinMode FUNC(ModeGet)(void *me,int PinNumber);
  PinResult FUNC(ModeSet)(void *me,int PinNumber,PinMode Mode);
  int InitStatus;
  unsigned LockBase;
  int deferlock;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetPinInit(tsctl *,int instance);
void *NetPinFini(NetPin *);
int32 NetPinLock(NetPin *ob,uint32 num,int32 flags);
int32 NetPinUnlock(NetPin *ob,uint32 num,int32 flags);
int32 NetPinPreempt(NetPin *ob);
PinMode NetPinModeGet(NetPin *ob,int32 PinNumber);
PinResult NetPinModeSet(NetPin *ob,int32 PinNumber,PinMode Mode);
#endif
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
