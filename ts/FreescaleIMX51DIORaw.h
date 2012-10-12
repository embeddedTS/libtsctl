#ifndef __FreescaleIMX51DIORaw_h
#define __FreescaleIMX51DIORaw_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct FreescaleIMX51DIORaw FreescaleIMX51DIORaw;
struct FreescaleIMX51DIORaw {
	void *FUNC(Init)(FreescaleIMX51DIORaw *me,void *bus);
	void FUNC(Fini)(FreescaleIMX51DIORaw *me);
	int FUNC(Lock)(FreescaleIMX51DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(FreescaleIMX51DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(FreescaleIMX51DIORaw *me);
	void FUNC(DirSet)(FreescaleIMX51DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(FreescaleIMX51DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(FreescaleIMX51DIORaw *me,int num);
	int FUNC(DataGet)(FreescaleIMX51DIORaw *me,int num);
	unsigned FUNC(Count)(FreescaleIMX51DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *FreescaleIMX51DIORawInit(FreescaleIMX51DIORaw* ob,void *bus);
void FreescaleIMX51DIORawFini(FreescaleIMX51DIORaw* ob);
int FreescaleIMX51DIORawLock(FreescaleIMX51DIORaw* ob,unsigned num,int flags);
int FreescaleIMX51DIORawUnlock(FreescaleIMX51DIORaw* ob,unsigned num,int flags);
int FreescaleIMX51DIORawPreempt(FreescaleIMX51DIORaw* ob);
void FreescaleIMX51DIORawDirSet(FreescaleIMX51DIORaw* ob,int num,int asOutput);
void FreescaleIMX51DIORawDataSet(FreescaleIMX51DIORaw* ob,int num,int asHigh);
int FreescaleIMX51DIORawDirGet(FreescaleIMX51DIORaw* ob,int num);
int FreescaleIMX51DIORawDataGet(FreescaleIMX51DIORaw* ob,int num);
unsigned FreescaleIMX51DIORawCount(FreescaleIMX51DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
