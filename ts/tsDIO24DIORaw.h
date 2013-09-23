#ifndef __tsDIO24DIORaw_h
#define __tsDIO24DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct tsDIO24DIORaw tsDIO24DIORaw;
struct tsDIO24DIORaw {
	void *FUNC(Init)(tsDIO24DIORaw *me,void *bus,int adrs);
	void FUNC(Fini)(tsDIO24DIORaw *me);
	int FUNC(Lock)(tsDIO24DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(tsDIO24DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(tsDIO24DIORaw *me);
	void FUNC(DirSet)(tsDIO24DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(tsDIO24DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(tsDIO24DIORaw *me,int num);
	int FUNC(DataGet)(tsDIO24DIORaw *me,int num);
	unsigned FUNC(Count)(tsDIO24DIORaw *me);
	int InitStatus;
	int deferlockW;
	int deferlockR;
	Bus *sub;
	int adrs;
};

void *tsDIO24DIORawInit(tsDIO24DIORaw* ob,void *bus,int adrs);
void tsDIO24DIORawFini(tsDIO24DIORaw* ob);
int tsDIO24DIORawLock(tsDIO24DIORaw* ob,unsigned num,int flags);
int tsDIO24DIORawUnlock(tsDIO24DIORaw* ob,unsigned num,int flags);
int tsDIO24DIORawPreempt(tsDIO24DIORaw* ob);
void tsDIO24DIORawDirSet(tsDIO24DIORaw* ob,int num,int asOutput);
void tsDIO24DIORawDataSet(tsDIO24DIORaw* ob,int num,int asHigh);
int tsDIO24DIORawDirGet(tsDIO24DIORaw* ob,int num);
int tsDIO24DIORawDataGet(tsDIO24DIORaw* ob,int num);
unsigned tsDIO24DIORawCount(tsDIO24DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
