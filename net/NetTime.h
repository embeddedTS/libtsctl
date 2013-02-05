#ifndef __NetTime_H
#define __NetTime_H
#include "Net2.h"
#include "Stream.h"
#include "Time.h"

typedef struct NetTime NetTime;

struct NetTime {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  unsigned FUNC(Wait)(void *me,unsigned microseconds);
  void FUNC(Delay)(void *me,unsigned microseconds);
  unsigned FUNC(Tick)(void *me);
  unsigned FUNC(usElapsed)(void *me,unsigned start);
  unsigned FUNC(usFuture)(void *me,unsigned start,unsigned microseconds);
  TimeResult FUNC(TimeoutQ)(void *me,unsigned start,unsigned end);
  unsigned FUNC(TPS)(void *me);
  int InitStatus;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetTimeInit(tsctl *,int instance);
void *NetTimeFini(NetTime *);
uint32 NetTimeWait(NetTime *ob,uint32 microseconds);
void NetTimeDelay(NetTime *ob,uint32 microseconds);
uint32 NetTimeTick(NetTime *ob);
uint32 NetTimeusElapsed(NetTime *ob,uint32 start);
uint32 NetTimeusFuture(NetTime *ob,uint32 start,uint32 microseconds);
TimeResult NetTimeTimeoutQ(NetTime *ob,uint32 start,uint32 end);
uint32 NetTimeTPS(NetTime *ob);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
