#ifndef __ts4700DIORaw_h
#define __ts4700DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4700DIORaw ts4700DIORaw;
struct ts4700DIORaw {
	void *FUNC(Init)(ts4700DIORaw *me,void *bus);
	void FUNC(Fini)(ts4700DIORaw *me);
	int FUNC(Lock)(ts4700DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4700DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4700DIORaw *me);
	void FUNC(DirSet)(ts4700DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts4700DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts4700DIORaw *me,int num);
	int FUNC(DataGet)(ts4700DIORaw *me,int num);
	unsigned FUNC(Count)(ts4700DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *ts4700DIORawInit(ts4700DIORaw* ob,void *bus);
void ts4700DIORawFini(ts4700DIORaw* ob);
int ts4700DIORawLock(ts4700DIORaw* ob,unsigned num,int flags);
int ts4700DIORawUnlock(ts4700DIORaw* ob,unsigned num,int flags);
int ts4700DIORawPreempt(ts4700DIORaw* ob);
void ts4700DIORawDirSet(ts4700DIORaw* ob,int num,int asOutput);
void ts4700DIORawDataSet(ts4700DIORaw* ob,int num,int asHigh);
int ts4700DIORawDirGet(ts4700DIORaw* ob,int num);
int ts4700DIORawDataGet(ts4700DIORaw* ob,int num);
unsigned ts4700DIORawCount(ts4700DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
