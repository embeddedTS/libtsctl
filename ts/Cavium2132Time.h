#ifndef __Cavium2132Time_h
#define __Cavium2132Time_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Cavium2132Time Cavium2132Time;
struct Cavium2132Time {
	void *FUNC(Init)(Cavium2132Time *me,...);
	void FUNC(Fini)(Cavium2132Time *me);
	unsigned FUNC(Wait)(Cavium2132Time *me,unsigned microseconds);
	void FUNC(Delay)(Cavium2132Time *me,unsigned microseconds);
	unsigned FUNC(Tick)(Cavium2132Time *me);
	unsigned FUNC(usElapsed)(Cavium2132Time *me,unsigned start);
	unsigned FUNC(usFuture)(Cavium2132Time *me,unsigned start,unsigned us);
	int FUNC(TimeoutQ)(Cavium2132Time *me,unsigned start,unsigned end);
	unsigned FUNC(TPS)(Cavium2132Time *me);
	int InitStatus;
	volatile unsigned *timer3;
};

void *Cavium2132TimeInit(Cavium2132Time* ob,...);
void Cavium2132TimeFini(Cavium2132Time* ob);
unsigned Cavium2132TimeWait(Cavium2132Time* ob,unsigned microseconds);
void Cavium2132TimeDelay(Cavium2132Time* ob,unsigned microseconds);
unsigned Cavium2132TimeTick(Cavium2132Time* ob);
unsigned Cavium2132TimeusElapsed(Cavium2132Time* ob,unsigned start);
unsigned Cavium2132TimeusFuture(Cavium2132Time* ob,unsigned start,unsigned us);
int Cavium2132TimeTimeoutQ(Cavium2132Time* ob,unsigned start,unsigned end);
unsigned Cavium2132TimeTPS(Cavium2132Time* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
