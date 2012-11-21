#ifndef __ts8820Pin_h
#define __ts8820Pin_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts8820Pin ts8820Pin;
struct ts8820Pin {
	void *FUNC(Init)(ts8820Pin *me,void *parent,void *bus,int start);
	void FUNC(Fini)(ts8820Pin *me);
	int FUNC(Lock)(ts8820Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts8820Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts8820Pin *me);
	PinMode FUNC(ModeGet)(ts8820Pin *me,int PinNumber);
	int FUNC(ModeSet)(ts8820Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	int deferlockR;
	int deferlockW;
	Pin *parent;
	Bus *bus;
	int start;
};

void *ts8820PinInit(ts8820Pin* ob,void *parent,void *bus,int start);
void ts8820PinFini(ts8820Pin* ob);
int ts8820PinLock(ts8820Pin* ob,unsigned num,int flags);
int ts8820PinUnlock(ts8820Pin* ob,unsigned num,int flags);
int ts8820PinPreempt(ts8820Pin* ob);
PinMode ts8820PinModeGet(ts8820Pin* ob,int PinNumber);
int ts8820PinModeSet(ts8820Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
