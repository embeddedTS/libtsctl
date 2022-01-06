#ifndef __ts81x0DIORaw_h
#define __ts81x0DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts81x0DIORaw ts81x0DIORaw;
struct ts81x0DIORaw {
	void *FUNC(Init)(ts81x0DIORaw *me,void *bus);
	void FUNC(Fini)(ts81x0DIORaw *me);
	int FUNC(Lock)(ts81x0DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts81x0DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts81x0DIORaw *me);
	void FUNC(DirSet)(ts81x0DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts81x0DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts81x0DIORaw *me,int num);
	int FUNC(DataGet)(ts81x0DIORaw *me,int num);
	unsigned FUNC(Count)(ts81x0DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
	int adrs;
};

void *ts81x0DIORawInit(ts81x0DIORaw* ob,void *bus);
void ts81x0DIORawFini(ts81x0DIORaw* ob);
int ts81x0DIORawLock(ts81x0DIORaw* ob,unsigned num,int flags);
int ts81x0DIORawUnlock(ts81x0DIORaw* ob,unsigned num,int flags);
int ts81x0DIORawPreempt(ts81x0DIORaw* ob);
void ts81x0DIORawDirSet(ts81x0DIORaw* ob,int num,int asOutput);
void ts81x0DIORawDataSet(ts81x0DIORaw* ob,int num,int asHigh);
int ts81x0DIORawDirGet(ts81x0DIORaw* ob,int num);
int ts81x0DIORawDataGet(ts81x0DIORaw* ob,int num);
unsigned ts81x0DIORawCount(ts81x0DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
