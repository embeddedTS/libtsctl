#ifndef __ts7670DIORaw_h
#define __ts7670DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts7670DIORaw ts7670DIORaw;
struct ts7670DIORaw {
	void *FUNC(Init)(ts7670DIORaw *me,void *bus);
	void FUNC(Fini)(ts7670DIORaw *me);
	int FUNC(Lock)(ts7670DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts7670DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts7670DIORaw *me);
	void FUNC(DirSet)(ts7670DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts7670DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts7670DIORaw *me,int num);
	int FUNC(DataGet)(ts7670DIORaw *me,int num);
	unsigned FUNC(Count)(ts7670DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *ts7670DIORawInit(ts7670DIORaw* ob,void *bus);
void ts7670DIORawFini(ts7670DIORaw* ob);
int ts7670DIORawLock(ts7670DIORaw* ob,unsigned num,int flags);
int ts7670DIORawUnlock(ts7670DIORaw* ob,unsigned num,int flags);
int ts7670DIORawPreempt(ts7670DIORaw* ob);
void ts7670DIORawDirSet(ts7670DIORaw* ob,int num,int asOutput);
void ts7670DIORawDataSet(ts7670DIORaw* ob,int num,int asHigh);
int ts7670DIORawDirGet(ts7670DIORaw* ob,int num);
int ts7670DIORawDataGet(ts7670DIORaw* ob,int num);
unsigned ts7670DIORawCount(ts7670DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
