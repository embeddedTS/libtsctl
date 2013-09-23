#ifndef __ts4800DIORaw_h
#define __ts4800DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4800DIORaw ts4800DIORaw;
struct ts4800DIORaw {
	void *FUNC(Init)(ts4800DIORaw *me,void *bus);
	void FUNC(Fini)(ts4800DIORaw *me);
	int FUNC(Lock)(ts4800DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4800DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4800DIORaw *me);
	void FUNC(DirSet)(ts4800DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts4800DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts4800DIORaw *me,int num);
	int FUNC(DataGet)(ts4800DIORaw *me,int num);
	unsigned FUNC(Count)(ts4800DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *ts4800DIORawInit(ts4800DIORaw* ob,void *bus);
void ts4800DIORawFini(ts4800DIORaw* ob);
int ts4800DIORawLock(ts4800DIORaw* ob,unsigned num,int flags);
int ts4800DIORawUnlock(ts4800DIORaw* ob,unsigned num,int flags);
int ts4800DIORawPreempt(ts4800DIORaw* ob);
void ts4800DIORawDirSet(ts4800DIORaw* ob,int num,int asOutput);
void ts4800DIORawDataSet(ts4800DIORaw* ob,int num,int asHigh);
int ts4800DIORawDirGet(ts4800DIORaw* ob,int num);
int ts4800DIORawDataGet(ts4800DIORaw* ob,int num);
unsigned ts4800DIORawCount(ts4800DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
