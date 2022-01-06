#ifndef __ts4500DIORaw_h
#define __ts4500DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4500DIORaw ts4500DIORaw;
struct ts4500DIORaw {
	void *FUNC(Init)(ts4500DIORaw *me,void *bus);
	void FUNC(Fini)(ts4500DIORaw *me);
	int FUNC(Lock)(ts4500DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4500DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4500DIORaw *me);
	void FUNC(DirSet)(ts4500DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts4500DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts4500DIORaw *me,int num);
	int FUNC(DataGet)(ts4500DIORaw *me,int num);
	unsigned FUNC(Count)(ts4500DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *ts4500DIORawInit(ts4500DIORaw* ob,void *bus);
void ts4500DIORawFini(ts4500DIORaw* ob);
int ts4500DIORawLock(ts4500DIORaw* ob,unsigned num,int flags);
int ts4500DIORawUnlock(ts4500DIORaw* ob,unsigned num,int flags);
int ts4500DIORawPreempt(ts4500DIORaw* ob);
void ts4500DIORawDirSet(ts4500DIORaw* ob,int num,int asOutput);
void ts4500DIORawDataSet(ts4500DIORaw* ob,int num,int asHigh);
int ts4500DIORawDirGet(ts4500DIORaw* ob,int num);
int ts4500DIORawDataGet(ts4500DIORaw* ob,int num);
unsigned ts4500DIORawCount(ts4500DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
