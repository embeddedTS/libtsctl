#ifndef __ts4800Pin_h
#define __ts4800Pin_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4800Pin ts4800Pin;
struct ts4800Pin {
	void *FUNC(Init)(ts4800Pin *me,void *syscon,void *dio1bus);
	void FUNC(Fini)(ts4800Pin *me);
	int FUNC(Lock)(ts4800Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4800Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4800Pin *me);
	PinMode FUNC(ModeGet)(ts4800Pin *me,int PinNumber);
	PinResult FUNC(ModeSet)(ts4800Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	Bus *bus;
};

void *ts4800PinInit(ts4800Pin* ob,void *syscon,void *dio1bus);
void ts4800PinFini(ts4800Pin* ob);
int ts4800PinLock(ts4800Pin* ob,unsigned num,int flags);
int ts4800PinUnlock(ts4800Pin* ob,unsigned num,int flags);
int ts4800PinPreempt(ts4800Pin* ob);
PinMode ts4800PinModeGet(ts4800Pin* ob,int PinNumber);
PinResult ts4800PinModeSet(ts4800Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
