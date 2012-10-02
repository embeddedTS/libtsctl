#include <sys/time.h>
#include "NetTime.h"

static TimeAPI NetTimeAPI = {
  .Init = (void *)NetTimeInit,
  .Fini = (void *)NetTimeFini,
  .Wait = (void *)NetTimeWait,
  .Delay = (void *)NetTimeDelay,
  .Tick = (void *)NetTimeTick,
  .usElapsed = (void *)NetTimeUSElapsed,
  .usFuture = (void *)NetTimeUSFuture,
  .TimeoutQ = (void *)NetTimeTimeoutQ,
  .TPS = (void *)NetTimeTPS
};

void *NetTimeInit(NetTime *me,int socket,int inst,int mode,Packet *q,int *cmds) {
  if (me->InitStatus > 0) return me;
  me->API = &NetTimeAPI;

  me->inst = inst;
  me->socket = socket;
  me->InitStatus = me->socket >= 0 ? 1 : -1;
  me->mode = mode;
  me->q = q;
  me->cmds = cmds;
  return me;
}

void NetTimeFini(NetTime *me) {
  //shutdown(me->socket,0);
  //close(me->socket);
  if (me->InitStatus > 0) me->InitStatus = 0;
}

unsigned NetTimeWait(NetTime *me,unsigned microseconds) {
  if (me->InitStatus < 0) return -1;
  PacketPushCmd(me->q,NetTime_Wait,me,NetTimeClass);
  PacketPush32(me->q,microseconds);
  return DoCmd(me->q,me,1);
}

void NetTimeDelay(NetTime *me,unsigned microseconds) {
  if (me->InitStatus < 0) return;
  PacketPushCmd(me->q,NetTime_Delay,me,NetTimeClass);
  PacketPush32(me->q,microseconds);
  DoCmd(me->q,me,0);
}

unsigned NetTimeTick(NetTime *me) {
  if (me->InitStatus < 0) return -1;
  PacketPushCmd(me->q,NetTime_Tick,me,NetTimeClass);
  return DoCmd(me->q,me,1);
}

unsigned NetTimeTPS(NetTime *me) {
  if (me->InitStatus < 0) return -1;
  PacketPushCmd(me->q,NetTime_TPS,me,NetTimeClass);
  return DoCmd(me->q,me,1);
}

unsigned NetTimeUSElapsed(NetTime *me,unsigned start) {
  if (me->InitStatus < 0) return -1;
  PacketPushCmd(me->q,NetTime_usElapsed,me,NetTimeClass);
  PacketPush32(me->q,start);
  return DoCmd(me->q,me,1);

}

unsigned NetTimeUSFuture(NetTime *me,unsigned start,unsigned us) {
  if (me->InitStatus < 0) return -1;
  PacketPushCmd(me->q,NetTime_usFuture,me,NetTimeClass);
  PacketPush32(me->q,start);
  PacketPush32(me->q,us);
  return DoCmd(me->q,me,1);
}

int NetTimeTimeoutQ(NetTime *me,unsigned start,unsigned end) {
  if (me->InitStatus < 0) return -1;
  PacketPushCmd(me->q,NetTime_TimeoutQ,me,NetTimeClass);
  PacketPush32(me->q,start);
  PacketPush32(me->q,end);
  return DoCmd(me->q,me,1);
}
/*
# Wait tested
tsctl Time m4500x8200:0 Wait 1000000
# Delay tested
tsctl Time m4500x8200:0 Delay 1000000
# Tick tested
tsctl Time m4500x8200:0 Tick;tsctl Time m4500x8200:0 Tick
# usElapsed
TICK=`tsctl Time m4500x8200:1 Tick`
tsctl Time m4500x8200:1 usElapsed $TICK
# usFuture
# TimeoutQ
TICK=`tsctl Time m4500x8200:1 Tick`
FUT=`tsctl Time m4500x8200:1 usFuture $TICK 4000000`
tsctl Time m4500x8200:1 TimeoutQ $TICK $FUT
# TPS tested
tsctl Time m4500x8200:0 TPS
 */
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
