#ifndef __NetTime_H
#define __NetTime_H
#include "Net.h"
#include "Time.h"

typedef struct NetTime NetTime;

struct NetTime {
  TimeAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetTimeInit(NetTime *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetTimeFini(NetTime *);
unsigned NetTimeWait(NetTime *,unsigned microseconds);
void NetTimeDelay(NetTime *,unsigned microseconds);
unsigned NetTimeTick(NetTime *);
unsigned NetTimeTPS(NetTime *);
unsigned NetTimeUSElapsed(NetTime *,unsigned start);
unsigned NetTimeUSFuture(NetTime *,unsigned start,unsigned us);
int NetTimeTimeoutQ(NetTime *,unsigned start,unsigned end);


#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
