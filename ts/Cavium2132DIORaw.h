#ifndef __Cavium2132DIORaw_h
#define __Cavium2132DIORaw_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Cavium2132DIORaw Cavium2132DIORaw;
struct Cavium2132DIORaw {
	void *FUNC(Init)(Cavium2132DIORaw *me,void *bus);
	void FUNC(Fini)(Cavium2132DIORaw *me);
	int FUNC(Lock)(Cavium2132DIORaw *me,unsigned num,int flags);
	int FUNC(Unlock)(Cavium2132DIORaw *me,unsigned num,int flags);
	int FUNC(Preempt)(Cavium2132DIORaw *me);
	void FUNC(DirSet)(Cavium2132DIORaw *me,int num,int asOutput);
	void FUNC(DataSet)(Cavium2132DIORaw *me,int num,int asHigh);
	int FUNC(DirGet)(Cavium2132DIORaw *me,int num);
	int FUNC(DataGet)(Cavium2132DIORaw *me,int num);
	unsigned FUNC(Count)(Cavium2132DIORaw *me);
	int InitStatus;
	int deferlockW;
	int deferlockR;
	Bus *sub;
};

void *Cavium2132DIORawInit(Cavium2132DIORaw* ob,void *bus);
void Cavium2132DIORawFini(Cavium2132DIORaw* ob);
int Cavium2132DIORawLock(Cavium2132DIORaw* ob,unsigned num,int flags);
int Cavium2132DIORawUnlock(Cavium2132DIORaw* ob,unsigned num,int flags);
int Cavium2132DIORawPreempt(Cavium2132DIORaw* ob);
void Cavium2132DIORawDirSet(Cavium2132DIORaw* ob,int num,int asOutput);
void Cavium2132DIORawDataSet(Cavium2132DIORaw* ob,int num,int asHigh);
int Cavium2132DIORawDirGet(Cavium2132DIORaw* ob,int num);
int Cavium2132DIORawDataGet(Cavium2132DIORaw* ob,int num);
unsigned Cavium2132DIORawCount(Cavium2132DIORaw* ob);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
