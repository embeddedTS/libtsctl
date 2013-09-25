#ifndef __ts7670Pin_h
#define __ts7670Pin_h
#include "Pin.h"
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts7670Pin ts7670Pin;
struct ts7670Pin {
	void *FUNC(Init)(ts7670Pin *me,void *sub);
	void FUNC(Fini)(ts7670Pin *me);
	int FUNC(Lock)(ts7670Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts7670Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts7670Pin *me);
	PinMode FUNC(ModeGet)(ts7670Pin *me,int PinNumber);
	PinResult FUNC(ModeSet)(ts7670Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	Bus *sub;
};

void *ts7670PinInit(ts7670Pin* ob,void *bus);
void ts7670PinFini(ts7670Pin* ob);
int ts7670PinLock(ts7670Pin* ob,unsigned num,int flags);
int ts7670PinUnlock(ts7670Pin* ob,unsigned num,int flags);
int ts7670PinPreempt(ts7670Pin* ob);
PinMode ts7670PinModeGet(ts7670Pin* ob,int PinNumber);
PinResult ts7670PinModeSet(ts7670Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
