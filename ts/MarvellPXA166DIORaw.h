#ifndef __MarvellPXA166DIORaw_h
#define __MarvellPXA166DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct MarvellPXA166DIORaw MarvellPXA166DIORaw;
struct MarvellPXA166DIORaw {
	void *FUNC(Init)(MarvellPXA166DIORaw *me,void *bus);
	void FUNC(Fini)(MarvellPXA166DIORaw *me);
	int FUNC(Lock)(MarvellPXA166DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(MarvellPXA166DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(MarvellPXA166DIORaw *me);
	void FUNC(DirSet)(MarvellPXA166DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(MarvellPXA166DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(MarvellPXA166DIORaw *me,int num);
	int FUNC(DataGet)(MarvellPXA166DIORaw *me,int num);
	unsigned FUNC(Count)(MarvellPXA166DIORaw *me);
	int InitStatus;
	int deferlockR;
	int deferlockW;
	Bus *sub;
};

void *MarvellPXA166DIORawInit(MarvellPXA166DIORaw* ob,void *bus);
void MarvellPXA166DIORawFini(MarvellPXA166DIORaw* ob);
int MarvellPXA166DIORawLock(MarvellPXA166DIORaw* ob,unsigned num,int flags);
int MarvellPXA166DIORawUnlock(MarvellPXA166DIORaw* ob,unsigned num,int flags);
int MarvellPXA166DIORawPreempt(MarvellPXA166DIORaw* ob);
void MarvellPXA166DIORawDirSet(MarvellPXA166DIORaw* ob,int num,int asOutput);
void MarvellPXA166DIORawDataSet(MarvellPXA166DIORaw* ob,int num,int asHigh);
int MarvellPXA166DIORawDirGet(MarvellPXA166DIORaw* ob,int num);
int MarvellPXA166DIORawDataGet(MarvellPXA166DIORaw* ob,int num);
unsigned MarvellPXA166DIORawCount(MarvellPXA166DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
