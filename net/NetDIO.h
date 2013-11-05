#ifndef __NetDIO_H
#define __NetDIO_H
#include "NetTsctl.h"
#include "DIO.h"

typedef struct NetDIO NetDIO;

struct NetDIO {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  void FUNC(Refresh)(void *me);
  void FUNC(Commit)(void *me,int ForceAll);
  void FUNC(Set)(void *me,int DIONum,DIOState State);
  DIOState FUNC(Get)(void *me,int DIONum);
  void FUNC(SetAsync)(void *me,int DIONum,DIOState State);
  DIOState FUNC(GetAsync)(void *me,int DIONum);
  void FUNC(Wait)(void *me,int *match,int min,int max,const int *nh,const int *nl);
  unsigned FUNC(Count)(void *me);
  DIOCaps FUNC(Capabilities)(void *me,unsigned num);
  int FUNC(GetMulti)(void *me,char *state,int offset);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetDIOInit(tsctl *,int instance);
void *NetDIOFini(NetDIO *);
int32 NetDIOLock(NetDIO *ob,uint32 num,int32 flags);
int32 NetDIOUnlock(NetDIO *ob,uint32 num,int32 flags);
int32 NetDIOPreempt(NetDIO *ob);
void NetDIORefresh(NetDIO *ob);
void NetDIOCommit(NetDIO *ob,int32 ForceAll);
void NetDIOSet(NetDIO *ob,int32 DIONum,DIOState State);
DIOState NetDIOGet(NetDIO *ob,int32 DIONum);
void NetDIOSetAsync(NetDIO *ob,int32 DIONum,DIOState State);
DIOState NetDIOGetAsync(NetDIO *ob,int32 DIONum);
void NetDIOWait(NetDIO *ob,int32* match,int32 min,int32 max,const int32* nh,const int32* nl);
uint32 NetDIOCount(NetDIO *ob);
DIOCaps NetDIOCapabilities(NetDIO *ob,uint32 num);
int32 NetDIOGetMulti(NetDIO *ob,int8* state,int32 offset);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
