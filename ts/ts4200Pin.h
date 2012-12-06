#ifndef __ts4200Pin_h
#define __ts4200Pin_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4200Pin ts4200Pin;
struct ts4200Pin {
	void *FUNC(Init)(ts4200Pin *me,void *bus,void *busb,void *buspmc,void *busc);
	void FUNC(Fini)(ts4200Pin *me);
	int FUNC(Lock)(ts4200Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4200Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4200Pin *me);
	PinMode FUNC(ModeGet)(ts4200Pin *me,int PinNumber);
	PinResult FUNC(ModeSet)(ts4200Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	Bus *syscon;
	Bus *piob;
	Bus *pmc;
	Bus *pioc;
};

void *ts4200PinInit(ts4200Pin* ob,void *bus,void *busb,void *buspmc,void *busc);
void ts4200PinFini(ts4200Pin* ob);
int ts4200PinLock(ts4200Pin* ob,unsigned num,int flags);
int ts4200PinUnlock(ts4200Pin* ob,unsigned num,int flags);
int ts4200PinPreempt(ts4200Pin* ob);
PinMode ts4200PinModeGet(ts4200Pin* ob,int PinNumber);
PinResult ts4200PinModeSet(ts4200Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
