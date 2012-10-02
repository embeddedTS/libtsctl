#ifndef __Cavium2132Time_H
#define __Cavium2132Time_H
#include "Time.h"

typedef struct Cavium2132Time Cavium2132Time;
struct Cavium2132Time {
  Time;
  int InitStatus;
  volatile unsigned *timer3;
};

void *Cavium2132TimeInit(Cavium2132Time *,...);
void Cavium2132TimeFini(Cavium2132Time *);
unsigned Cavium2132TimeWait(Cavium2132Time *,unsigned microseconds);
void Cavium2132TimeDelay(Cavium2132Time *,unsigned microseconds);
unsigned Cavium2132TimeTick(Cavium2132Time *);
unsigned Cavium2132TimeTPS(Cavium2132Time *);
unsigned Cavium2132USElapsed(Cavium2132Time *,unsigned start);
unsigned Cavium2132USFuture(Cavium2132Time *,unsigned start,unsigned us);
unsigned Cavium2132TimeoutQ(Cavium2132Time *,unsigned start,unsigned end);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
