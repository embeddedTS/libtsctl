#ifndef __ts8900DIORaw_h
#define __ts8900DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts8900DIORaw ts8900DIORaw;
struct ts8900DIORaw {
	void *FUNC(Init)(ts8900DIORaw *me,void *bus);
	void FUNC(Fini)(ts8900DIORaw *me);
	int FUNC(Lock)(ts8900DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts8900DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts8900DIORaw *me);
	void FUNC(DirSet)(ts8900DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts8900DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts8900DIORaw *me,int num);
	int FUNC(DataGet)(ts8900DIORaw *me,int num);
	unsigned FUNC(Count)(ts8900DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
	int adrs;
};

void *ts8900DIORawInit(ts8900DIORaw* ob,void *bus);
void ts8900DIORawFini(ts8900DIORaw* ob);
int ts8900DIORawLock(ts8900DIORaw* ob,unsigned num,int flags);
int ts8900DIORawUnlock(ts8900DIORaw* ob,unsigned num,int flags);
int ts8900DIORawPreempt(ts8900DIORaw* ob);
void ts8900DIORawDirSet(ts8900DIORaw* ob,int num,int asOutput);
void ts8900DIORawDataSet(ts8900DIORaw* ob,int num,int asHigh);
int ts8900DIORawDirGet(ts8900DIORaw* ob,int num);
int ts8900DIORawDataGet(ts8900DIORaw* ob,int num);
unsigned ts8900DIORawCount(ts8900DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
