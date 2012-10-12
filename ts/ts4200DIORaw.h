#ifndef __ts4200DIORaw_h
#define __ts4200DIORaw_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4200DIORaw ts4200DIORaw;
struct ts4200DIORaw {
	void *FUNC(Init)(ts4200DIORaw *me,void *bus);
	void FUNC(Fini)(ts4200DIORaw *me);
	int FUNC(Lock)(ts4200DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4200DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4200DIORaw *me);
	void FUNC(DirSet)(ts4200DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts4200DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts4200DIORaw *me,int num);
	int FUNC(DataGet)(ts4200DIORaw *me,int num);
	unsigned FUNC(Count)(ts4200DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *ts4200DIORawInit(ts4200DIORaw* ob,void *bus);
void ts4200DIORawFini(ts4200DIORaw* ob);
int ts4200DIORawLock(ts4200DIORaw* ob,unsigned num,int flags);
int ts4200DIORawUnlock(ts4200DIORaw* ob,unsigned num,int flags);
int ts4200DIORawPreempt(ts4200DIORaw* ob);
void ts4200DIORawDirSet(ts4200DIORaw* ob,int num,int asOutput);
void ts4200DIORawDataSet(ts4200DIORaw* ob,int num,int asHigh);
int ts4200DIORawDirGet(ts4200DIORaw* ob,int num);
int ts4200DIORawDataGet(ts4200DIORaw* ob,int num);
unsigned ts4200DIORawCount(ts4200DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
