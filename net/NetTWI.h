#ifndef __NetTWI_H
#define __NetTWI_H
#include "TWI.h"

typedef struct NetTWI NetTWI;

struct NetTWI {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  TWIResult FUNC(Write)(void *me,int devadr,int adrslen,int adrs,const char *bytes);
  TWIResult FUNC(Read)(void *me,int devadr,int adrslen,int adrs,char *bytes);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetTWIInit(tsctl *,int instance);
void *NetTWIFini(NetTWI *);
int32 NetTWILock(NetTWI *ob,uint32 num,int32 flags);
int32 NetTWIUnlock(NetTWI *ob,uint32 num,int32 flags);
int32 NetTWIPreempt(NetTWI *ob);
TWIResult NetTWIWrite(NetTWI *ob,int32 devadr,int32 adrslen,int32 adrs,const int8* bytes);
TWIResult NetTWIRead(NetTWI *ob,int32 devadr,int32 adrslen,int32 adrs,int8* bytes);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
