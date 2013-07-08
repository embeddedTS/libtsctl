#ifndef __ts7700DIORaw_h
#define __ts7700DIORaw_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts7700DIORaw ts7700DIORaw;
struct ts7700DIORaw {
	void *FUNC(Init)(ts7700DIORaw *me,void *bus);
	void FUNC(Fini)(ts7700DIORaw *me);
	int FUNC(Lock)(ts7700DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(ts7700DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(ts7700DIORaw *me);
	void FUNC(DirSet)(ts7700DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(ts7700DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(ts7700DIORaw *me,int num);
	int FUNC(DataGet)(ts7700DIORaw *me,int num);
	unsigned FUNC(Count)(ts7700DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *ts7700DIORawInit(ts7700DIORaw* ob,void *bus);
void ts7700DIORawFini(ts7700DIORaw* ob);
int ts7700DIORawLock(ts7700DIORaw* ob,unsigned num,int flags);
int ts7700DIORawUnlock(ts7700DIORaw* ob,unsigned num,int flags);
int ts7700DIORawPreempt(ts7700DIORaw* ob);
void ts7700DIORawDirSet(ts7700DIORaw* ob,int num,int asOutput);
void ts7700DIORawDataSet(ts7700DIORaw* ob,int num,int asHigh);
int ts7700DIORawDirGet(ts7700DIORaw* ob,int num);
int ts7700DIORawDataGet(ts7700DIORaw* ob,int num);
unsigned ts7700DIORawCount(ts7700DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2013, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
