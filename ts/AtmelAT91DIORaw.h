#ifndef __AtmelAT91DIORaw_h
#define __AtmelAT91DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct AtmelAT91DIORaw AtmelAT91DIORaw;
struct AtmelAT91DIORaw {
	void *FUNC(Init)(AtmelAT91DIORaw *me,void *bus);
	void FUNC(Fini)(AtmelAT91DIORaw *me);
	int FUNC(Lock)(AtmelAT91DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(AtmelAT91DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(AtmelAT91DIORaw *me);
	void FUNC(DirSet)(AtmelAT91DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(AtmelAT91DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(AtmelAT91DIORaw *me,int num);
	int FUNC(DataGet)(AtmelAT91DIORaw *me,int num);
	unsigned FUNC(Count)(AtmelAT91DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *AtmelAT91DIORawInit(AtmelAT91DIORaw* ob,void *bus);
void AtmelAT91DIORawFini(AtmelAT91DIORaw* ob);
int AtmelAT91DIORawLock(AtmelAT91DIORaw* ob,unsigned num,int flags);
int AtmelAT91DIORawUnlock(AtmelAT91DIORaw* ob,unsigned num,int flags);
int AtmelAT91DIORawPreempt(AtmelAT91DIORaw* ob);
void AtmelAT91DIORawDirSet(AtmelAT91DIORaw* ob,int num,int asOutput);
void AtmelAT91DIORawDataSet(AtmelAT91DIORaw* ob,int num,int asHigh);
int AtmelAT91DIORawDirGet(AtmelAT91DIORaw* ob,int num);
int AtmelAT91DIORawDataGet(AtmelAT91DIORaw* ob,int num);
unsigned AtmelAT91DIORawCount(AtmelAT91DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
