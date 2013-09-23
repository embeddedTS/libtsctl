#ifndef __ts4700Pin_h
#define __ts4700Pin_h
#include "Pin.h"
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4700Pin ts4700Pin;
struct ts4700Pin {
	void *FUNC(Init)(ts4700Pin *me,void *diobus,void *mfpbus);
	void FUNC(Fini)(ts4700Pin *me);
	int FUNC(Lock)(ts4700Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4700Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4700Pin *me);
	PinMode FUNC(ModeGet)(ts4700Pin *me,int PinNumber);
	PinResult FUNC(ModeSet)(ts4700Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	Bus *diobus;
	Bus *mfpbus;
};

void *ts4700PinInit(ts4700Pin* ob,void *diobus,void *mfpbus);
void ts4700PinFini(ts4700Pin* ob);
int ts4700PinLock(ts4700Pin* ob,unsigned num,int flags);
int ts4700PinUnlock(ts4700Pin* ob,unsigned num,int flags);
int ts4700PinPreempt(ts4700Pin* ob);
PinMode ts4700PinModeGet(ts4700Pin* ob,int PinNumber);
PinResult ts4700PinModeSet(ts4700Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
