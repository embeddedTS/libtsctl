#ifndef __ts4600DIO_h
#define __ts4600DIO_h
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4600DIO ts4600DIO;
struct ts4600DIO {
	void *FUNC(Init)(ts4600DIO *me,void *bus);
	void FUNC(Fini)(ts4600DIO *me);
	int FUNC(Lock)(ts4600DIO *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4600DIO *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4600DIO *me);
	void FUNC(Refresh)(ts4600DIO *me);
	void FUNC(Commit)(ts4600DIO *me,int ForceAll);
	void FUNC(Set)(ts4600DIO *me,int DIONum,DIOState State);
	DIOState FUNC(Get)(ts4600DIO *me,int DIONum);
	void FUNC(SetAsync)(ts4600DIO *me,int DIONum,DIOState State);
	DIOState FUNC(GetAsync)(ts4600DIO *me,int DIONum);
	void FUNC(Wait)(ts4600DIO *me,int *match,int min,int max,const int *nh,const int *nl);
	unsigned FUNC(Count)(ts4600DIO *me);
	DIOCaps FUNC(Capabilities)(ts4600DIO *me,unsigned num);
	int FUNC(GetMulti)(ts4600DIO *me,char *state,int offset);
	int InitStatus;
	unsigned NumLocks;
	Bus *bus;
	int gotHUP;
	unsigned char *Caps;
	int *dirCache;
};

void *ts4600DIOInit(ts4600DIO* ob,void *bus);
void ts4600DIOFini(ts4600DIO* ob);
int ts4600DIOLock(ts4600DIO* ob,unsigned num,int flags);
int ts4600DIOUnlock(ts4600DIO* ob,unsigned num,int flags);
int ts4600DIOPreempt(ts4600DIO* ob);
void ts4600DIORefresh(ts4600DIO* ob);
void ts4600DIOCommit(ts4600DIO* ob,int ForceAll);
void ts4600DIOSet(ts4600DIO* ob,int DIONum,DIOState State);
DIOState ts4600DIOGet(ts4600DIO* ob,int DIONum);
void ts4600DIOSetAsync(ts4600DIO* ob,int DIONum,DIOState State);
DIOState ts4600DIOGetAsync(ts4600DIO* ob,int DIONum);
void ts4600DIOWait(ts4600DIO* ob,int *match,int min,int max,const int *nh,const int *nl);
unsigned ts4600DIOCount(ts4600DIO* ob);
DIOCaps ts4600DIOCapabilities(ts4600DIO* ob,unsigned num);
int ts4600DIOGetMulti(ts4600DIO* ob,char *state,int offset);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
