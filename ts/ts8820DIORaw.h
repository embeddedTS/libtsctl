#ifndef __ts8820DIORaw_h
#define __ts8820DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts8820DIORaw ts8820DIORaw;
struct ts8820DIORaw {
	void *FUNC(Init)(ts8820DIORaw *me,void *bus);
	void FUNC(Fini)(ts8820DIORaw *me);
	int FUNC(Lock)(ts8820DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts8820DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts8820DIORaw *me);
	void FUNC(DirSet)(ts8820DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts8820DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts8820DIORaw *me,int num);
	int FUNC(DataGet)(ts8820DIORaw *me,int num);
	unsigned FUNC(Count)(ts8820DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
	int adrs;
};

void *ts8820DIORawInit(ts8820DIORaw* ob,void *bus);
void ts8820DIORawFini(ts8820DIORaw* ob);
int ts8820DIORawLock(ts8820DIORaw* ob,unsigned num,int flags);
int ts8820DIORawUnlock(ts8820DIORaw* ob,unsigned num,int flags);
int ts8820DIORawPreempt(ts8820DIORaw* ob);
void ts8820DIORawDirSet(ts8820DIORaw* ob,int num,int asOutput);
void ts8820DIORawDataSet(ts8820DIORaw* ob,int num,int asHigh);
int ts8820DIORawDirGet(ts8820DIORaw* ob,int num);
int ts8820DIORawDataGet(ts8820DIORaw* ob,int num);
unsigned ts8820DIORawCount(ts8820DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
