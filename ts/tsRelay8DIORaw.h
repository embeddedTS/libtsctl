#ifndef __tsRelay8DIORaw_h
#define __tsRelay8DIORaw_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct tsRelay8DIORaw tsRelay8DIORaw;
struct tsRelay8DIORaw {
	void *FUNC(Init)(tsRelay8DIORaw *me,void *bus,int adrs);
	void FUNC(Fini)(tsRelay8DIORaw *me);
	int FUNC(Lock)(tsRelay8DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(tsRelay8DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(tsRelay8DIORaw *me);
	void FUNC(DirSet)(tsRelay8DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(tsRelay8DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(tsRelay8DIORaw *me,int num);
	int FUNC(DataGet)(tsRelay8DIORaw *me,int num);
	unsigned FUNC(Count)(tsRelay8DIORaw *me);
	int InitStatus;
	int deferlockW;
	int deferlockR;
	Bus *sub;
	int adrs;
};

void *tsRelay8DIORawInit(tsRelay8DIORaw* ob,void *bus,int adrs);
void tsRelay8DIORawFini(tsRelay8DIORaw* ob);
int tsRelay8DIORawLock(tsRelay8DIORaw* ob,unsigned num,int flags);
int tsRelay8DIORawUnlock(tsRelay8DIORaw* ob,unsigned num,int flags);
int tsRelay8DIORawPreempt(tsRelay8DIORaw* ob);
void tsRelay8DIORawDirSet(tsRelay8DIORaw* ob,int num,int asOutput);
void tsRelay8DIORawDataSet(tsRelay8DIORaw* ob,int num,int asHigh);
int tsRelay8DIORawDirGet(tsRelay8DIORaw* ob,int num);
int tsRelay8DIORawDataGet(tsRelay8DIORaw* ob,int num);
unsigned tsRelay8DIORawCount(tsRelay8DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
