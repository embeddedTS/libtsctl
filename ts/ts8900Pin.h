#ifndef __ts8900Pin_h
#define __ts8900Pin_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts8900Pin ts8900Pin;
struct ts8900Pin {
	void *FUNC(Init)(ts8900Pin *me,void *parent,void *bus,int start);
	void FUNC(Fini)(ts8900Pin *me);
	int FUNC(Lock)(ts8900Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts8900Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts8900Pin *me);
	PinMode FUNC(ModeGet)(ts8900Pin *me,int PinNumber);
	PinResult FUNC(ModeSet)(ts8900Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	int deferlockR;
	int deferlockW;
	Pin *parent;
	Bus *bus;
	int start;
};

void *ts8900PinInit(ts8900Pin* ob,void *parent,void *bus,int start);
void ts8900PinFini(ts8900Pin* ob);
int ts8900PinLock(ts8900Pin* ob,unsigned num,int flags);
int ts8900PinUnlock(ts8900Pin* ob,unsigned num,int flags);
int ts8900PinPreempt(ts8900Pin* ob);
PinMode ts8900PinModeGet(ts8900Pin* ob,int PinNumber);
PinResult ts8900PinModeSet(ts8900Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
