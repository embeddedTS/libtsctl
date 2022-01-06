#ifndef __ts8820EDIO_h
#define __ts8820EDIO_h
#include "Pin.h"
#include "Bus.h"
#include "EDIO.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts8820EDIO ts8820EDIO;
struct ts8820EDIO {
	void *FUNC(Init)(ts8820EDIO *me,Bus *bus,Pin *pin,int start);
	void FUNC(Fini)(ts8820EDIO *me);
	int FUNC(Lock)(ts8820EDIO *me,unsigned num,int flags);
	int FUNC(Unlock)(ts8820EDIO *me,unsigned num,int flags);
	int FUNC(Preempt)(ts8820EDIO *me);
	int *FUNC(QueryFunction)(ts8820EDIO *me,EDIOType type);
	int FUNC(PWM)(ts8820EDIO *me,int num,unsigned periodHigh,unsigned periodLow);
	int FUNC(QueryPWM)(ts8820EDIO *me,int num,unsigned periodHigh[1],unsigned periodLow[1]);
	int FUNC(PWMfd)(ts8820EDIO *me,int num,unsigned freq,unsigned DC);
	int FUNC(QueryPWMfd)(ts8820EDIO *me,int num,unsigned freq[1],unsigned DC[1]);
	int FUNC(QuadratureCount)(ts8820EDIO *me,int num);
	unsigned long long FUNC(EdgeCount)(ts8820EDIO *me,int num,int edge);
	int FUNC(Glitched)(ts8820EDIO *me,int num);
	int FUNC(HBridge)(ts8820EDIO *me,int num,HBState state);
	int InitStatus;
	Bus *bus;
	Pin *pin;
	int start;
};

void *ts8820EDIOInit(ts8820EDIO* ob,Bus *bus,Pin *pin,int start);
void ts8820EDIOFini(ts8820EDIO* ob);
int ts8820EDIOLock(ts8820EDIO* ob,unsigned num,int flags);
int ts8820EDIOUnlock(ts8820EDIO* ob,unsigned num,int flags);
int ts8820EDIOPreempt(ts8820EDIO* ob);
int *ts8820EDIOQueryFunction(ts8820EDIO* ob,EDIOType type);
int ts8820EDIOPWM(ts8820EDIO* ob,int num,unsigned periodHigh,unsigned periodLow);
int ts8820EDIOQueryPWM(ts8820EDIO* ob,int num,unsigned periodHigh[1],unsigned periodLow[1]);
int ts8820EDIOPWMfd(ts8820EDIO* ob,int num,unsigned freq,unsigned DC);
int ts8820EDIOQueryPWMfd(ts8820EDIO* ob,int num,unsigned freq[1],unsigned DC[1]);
int ts8820EDIOQuadratureCount(ts8820EDIO* ob,int num);
unsigned long long ts8820EDIOEdgeCount(ts8820EDIO* ob,int num,int edge);
int ts8820EDIOGlitched(ts8820EDIO* ob,int num);
int ts8820EDIOHBridge(ts8820EDIO* ob,int num,HBState state);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
