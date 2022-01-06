#ifndef __NetDIORaw_H
#define __NetDIORaw_H
#include "NetTsctl.h"
#include "DIORaw.h"

typedef struct NetDIORaw NetDIORaw;

struct NetDIORaw {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  void FUNC(DirSet)(void *me,int num,int asOutput);
  void FUNC(DataSet)(void *me,int num,int asHigh);
  int FUNC(DirGet)(void *me,int num);
  int FUNC(DataGet)(void *me,int num);
  unsigned FUNC(Count)(void *me);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetDIORawInit(tsctl *,int instance);
void *NetDIORawFini(NetDIORaw *);
int32 NetDIORawLock(NetDIORaw *ob,uint32 num,int32 flags);
int32 NetDIORawUnlock(NetDIORaw *ob,uint32 num,int32 flags);
int32 NetDIORawPreempt(NetDIORaw *ob);
void NetDIORawDirSet(NetDIORaw *ob,int32 num,int32 asOutput);
void NetDIORawDataSet(NetDIORaw *ob,int32 num,int32 asHigh);
int32 NetDIORawDirGet(NetDIORaw *ob,int32 num);
int32 NetDIORawDataGet(NetDIORaw *ob,int32 num);
uint32 NetDIORawCount(NetDIORaw *ob);
#endif
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
