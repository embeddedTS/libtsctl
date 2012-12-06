#ifndef __ts81x0Pin_h
#define __ts81x0Pin_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts81x0Pin ts81x0Pin;
struct ts81x0Pin {
	void *FUNC(Init)(ts81x0Pin *me,void *parent,void *bus);
	void FUNC(Fini)(ts81x0Pin *me);
	int FUNC(Lock)(ts81x0Pin *me,unsigned num,int flags);
	int FUNC(Unlock)(ts81x0Pin *me,unsigned num,int flags);
	int FUNC(Preempt)(ts81x0Pin *me);
	PinMode FUNC(ModeGet)(ts81x0Pin *me,int PinNumber);
	PinResult FUNC(ModeSet)(ts81x0Pin *me,int PinNumber,PinMode Mode);
	int InitStatus;
	unsigned LockBase;
	int deferlock;
	int deferlockR;
	int deferlockW;
	Pin *parent;
	Bus *bus;
	int CAN_TX1;
	int CAN_TX2;
	int CAN_RX1;
	int CAN_RX2;
};

void *ts81x0PinInit(ts81x0Pin* ob,void *parent,void *bus);
void ts81x0PinFini(ts81x0Pin* ob);
int ts81x0PinLock(ts81x0Pin* ob,unsigned num,int flags);
int ts81x0PinUnlock(ts81x0Pin* ob,unsigned num,int flags);
int ts81x0PinPreempt(ts81x0Pin* ob);
PinMode ts81x0PinModeGet(ts81x0Pin* ob,int PinNumber);
PinResult ts81x0PinModeSet(ts81x0Pin* ob,int PinNumber,PinMode Mode);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
