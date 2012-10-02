#ifndef __TSTime_H
#define __TSTime_H
#include "Time.h"

typedef struct TSTime TSTime;
struct TSTime {
  Time;
  Bus *bus;
  int adrsMSB, adrsLSB, Hz;
};

void *TSTimeInit(TSTime *,void *bus,int adrsMSB,int adrsLSB,int Hz);
void TSTimeFini(TSTime *);
unsigned TSTimeWait(TSTime *,unsigned microseconds);
void TSTimeDelay(TSTime *,unsigned microseconds);
unsigned TSTimeTick(TSTime *);
unsigned TSTimeTPS(TSTime *);
unsigned TSUSElapsed(TSTime *,unsigned start);
unsigned TSUSFuture(TSTime *,unsigned start,unsigned us);
unsigned TSTimeoutQ(TSTime *,unsigned start,unsigned end);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
