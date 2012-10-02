#ifndef _ts8820EDIO_H
#define _ts8820EDIO_H
#include "EDIO.h"
#include "Bus.h"
#include "Pin.h"

typedef struct ts8820EDIO ts8820EDIO;

struct ts8820EDIO {
  EDIO;
  Bus *bus;
  Pin *pin;
  int start;
};

void *ts8820EDIOInit(ts8820EDIO *me,Bus *bus,Pin *pin,int start);
void ts8820EDIOFini(ts8820EDIO *me);
int ts8820EDIOLock(ts8820EDIO *me,unsigned num,int flags);
int ts8820EDIOUnlock(ts8820EDIO *me,unsigned num,int flags);
int ts8820EDIOPreempt(ts8820EDIO *me);
int* ts8820EDIOQueryFunction(ts8820EDIO *me,EDIOType type);
int ts8820EDIOPWM(ts8820EDIO *me,int num,unsigned periodHigh,unsigned periodLow);
int ts8820EDIOQueryPWM(ts8820EDIO *me,int num,unsigned periodHigh[1],unsigned periodLow[1]);
int ts8820EDIOPWMfd(ts8820EDIO *me,int num,unsigned freq,unsigned DC);
int ts8820EDIOQueryPWMfd(ts8820EDIO *me,int num,unsigned freq[1],unsigned DC[1]);
int ts8820EDIOQuadratureCount(ts8820EDIO *me,int num);
unsigned long long ts8820EDIOEdgeCount(ts8820EDIO *me,int num,int edge);
int ts8820EDIOGlitched(ts8820EDIO *me,int num);
int ts8820EDIOHBridge(ts8820EDIO *me,int num,HBState state);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
