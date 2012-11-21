#ifndef __SystemTime_h
#define __SystemTime_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct SystemTime SystemTime;
struct SystemTime {
	void *FUNC(Init)(SystemTime *me,...);
	void FUNC(Fini)(SystemTime *me);
	unsigned FUNC(Wait)(SystemTime *me,unsigned microseconds);
	void FUNC(Delay)(SystemTime *me,unsigned microseconds);
	unsigned FUNC(Tick)(SystemTime *me);
	unsigned FUNC(usElapsed)(SystemTime *me,unsigned start);
	unsigned FUNC(usFuture)(SystemTime *me,unsigned start,unsigned microseconds);
	int FUNC(TimeoutQ)(SystemTime *me,unsigned start,unsigned end);
	unsigned FUNC(TPS)(SystemTime *me);
	int InitStatus;
};

void *SystemTimeInit(SystemTime* ob,...);
void SystemTimeFini(SystemTime* ob);
unsigned SystemTimeWait(SystemTime* ob,unsigned microseconds);
void SystemTimeDelay(SystemTime* ob,unsigned microseconds);
unsigned SystemTimeTick(SystemTime* ob);
unsigned SystemTimeusElapsed(SystemTime* ob,unsigned start);
unsigned SystemTimeusFuture(SystemTime* ob,unsigned start,unsigned microseconds);
int SystemTimeTimeoutQ(SystemTime* ob,unsigned start,unsigned end);
unsigned SystemTimeTPS(SystemTime* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
