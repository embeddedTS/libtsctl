#ifndef __NetSystem_H
#define __NetSystem_H
#include "NetTsctl.h"
#include "System.h"

typedef struct NetSystem NetSystem;

struct NetSystem {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(ClassCount)(void *me);
  int FUNC(InstanceCount)(void *me,int ClassNumber);
  int FUNC(APICount)(void *me,int ClassNumber);
  int FUNC(LockCount)(void *me);
  LockHolderInf*FUNC(LockHolderInfo)(void *me);
  ConnectionWaitInf*FUNC(ConnWaitInfo)(void *me);
  SystemResult FUNC(CANBusGet)(void *me,int CANInstance);
  unsigned FUNC(BuildTime)(void *me);
  int FUNC(ModelId)(void *me);
  int FUNC(BaseBoardId)(void *me);
  int FUNC(MapLength)(void *me);
  char *FUNC(MapGet)(void *me,int MapIndex,int Value[1]);
  int FUNC(MapLookup)(void *me,const char *String);
  char *FUNC(MapLookupPartial)(void *me,const char *StringPrefix,int Value);
  SystemResult FUNC(MapAdd)(void *me,const char *String,int Value);
  SystemResult FUNC(MapDelete)(void *me,const char *String);
  char *FUNC(Note)(void *me,const char *Message);
  char *FUNC(Version)(void *me);
  unsigned FUNC(UptimeServer)(void *me);
  unsigned FUNC(UptimeHost)(void *me);
  int FUNC(FPGARevision)(void *me);
  int FUNC(EchoNumber)(void *me,int n);
  int InitStatus;
  unsigned maplock;
  NameValuePair *map;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetSystemInit(tsctl *,int instance);
void *NetSystemFini(NetSystem *);
int32 NetSystemClassCount(NetSystem *ob);
int32 NetSystemInstanceCount(NetSystem *ob,int32 ClassNumber);
int32 NetSystemAPICount(NetSystem *ob,int32 ClassNumber);
int32 NetSystemLockCount(NetSystem *ob);
LockHolderInf* NetSystemLockHolderInfo(NetSystem *ob);
ConnectionWaitInf* NetSystemConnWaitInfo(NetSystem *ob);
SystemResult NetSystemCANBusGet(NetSystem *ob,int32 CANInstance);
uint32 NetSystemBuildTime(NetSystem *ob);
int32 NetSystemModelId(NetSystem *ob);
int32 NetSystemBaseBoardId(NetSystem *ob);
int32 NetSystemMapLength(NetSystem *ob);
int8* NetSystemMapGet(NetSystem *ob,int32 MapIndex,int32 Value[1]);
int32 NetSystemMapLookup(NetSystem *ob,const int8* String);
int8* NetSystemMapLookupPartial(NetSystem *ob,const int8* StringPrefix,int32 Value);
SystemResult NetSystemMapAdd(NetSystem *ob,const int8* String,int32 Value);
SystemResult NetSystemMapDelete(NetSystem *ob,const int8* String);
int8* NetSystemNote(NetSystem *ob,const int8* Message);
int8* NetSystemVersion(NetSystem *ob);
uint32 NetSystemUptimeServer(NetSystem *ob);
uint32 NetSystemUptimeHost(NetSystem *ob);
int32 NetSystemFPGARevision(NetSystem *ob);
int32 NetSystemEchoNumber(NetSystem *ob,int32 n);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
