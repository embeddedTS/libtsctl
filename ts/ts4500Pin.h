#ifndef __ts4500Pin_h
#define __ts4500Pin_h
#include "Pin.h"
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4500Pin ts4500Pin;
struct ts4500Pin {
	void *FUNC(Init)(ts4500Pin *me,void *sbus,void *cpubus,void *confbus,int confadrs);
	void FUNC(Fini)(ts4500Pin *me);
	int FUNC(Lock)(ts4500Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4500Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4500Pin *me);
	PinMode FUNC(ModeGet)(ts4500Pin *me,int PinNumber);
	PinResult FUNC(ModeSet)(ts4500Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	Bus *sbus;
	Bus *cpubus;
	Bus *confbus;
	int confadrs;
};

void *ts4500PinInit(ts4500Pin* ob,void *sbus,void *cpubus,void *confbus,int confadrs);
void ts4500PinFini(ts4500Pin* ob);
int ts4500PinLock(ts4500Pin* ob,unsigned num,int flags);
int ts4500PinUnlock(ts4500Pin* ob,unsigned num,int flags);
int ts4500PinPreempt(ts4500Pin* ob);
PinMode ts4500PinModeGet(ts4500Pin* ob,int PinNumber);
PinResult ts4500PinModeSet(ts4500Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
