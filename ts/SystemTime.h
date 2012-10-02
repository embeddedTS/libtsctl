#ifndef __SystemTime_H
#define __SystemTime_H
#include "Time.h"

typedef struct Time SystemTime;

void *SystemTimeInit(SystemTime *,...);
void SystemTimeFini(SystemTime *);
unsigned SystemTimeWait(SystemTime *,unsigned microseconds);
void SystemTimeDelay(SystemTime *,unsigned microseconds);
unsigned SystemTimeTick(SystemTime *);
unsigned SystemTimeTPS(SystemTime *);
unsigned SystemTimeUSElapsed(SystemTime *,unsigned start);
unsigned SystemTimeUSFuture(SystemTime *,unsigned start,unsigned us);
int SystemTimeTimeoutQ(SystemTime *,unsigned start,unsigned end);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
