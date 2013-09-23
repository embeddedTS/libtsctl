#ifndef __ts4200DIO_h
#define __ts4200DIO_h
#include "DIO.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct ts4200DIO ts4200DIO;
struct ts4200DIO {
	void *FUNC(Init)(ts4200DIO *me,...);
	void FUNC(Fini)(ts4200DIO *me);
	int FUNC(Lock)(ts4200DIO *me,unsigned num,int flags);
	int FUNC(Unlock)(ts4200DIO *me,unsigned num,int flags);
	int FUNC(Preempt)(ts4200DIO *me);
	void FUNC(Refresh)(ts4200DIO *me);
	void FUNC(Commit)(ts4200DIO *me,int ForceAll);
	void FUNC(Set)(ts4200DIO *me,int DIONum,DIOState State);
	DIOState FUNC(Get)(ts4200DIO *me,int DIONum);
	void FUNC(SetAsync)(ts4200DIO *me,int DIONum,DIOState State);
	DIOState FUNC(GetAsync)(ts4200DIO *me,int DIONum);
	void FUNC(Wait)(ts4200DIO *me,int *match,int min,int max,const int *nh,const int *nl);
	unsigned FUNC(Count)(ts4200DIO *me);
	DIOCaps FUNC(Capabilities)(ts4200DIO *me,unsigned num);
	int FUNC(GetMulti)(ts4200DIO *me,char *state,int offset);
	int InitStatus;
};

void *ts4200DIOInit(ts4200DIO* ob,...);
void ts4200DIOFini(ts4200DIO* ob);
int ts4200DIOLock(ts4200DIO* ob,unsigned num,int flags);
int ts4200DIOUnlock(ts4200DIO* ob,unsigned num,int flags);
int ts4200DIOPreempt(ts4200DIO* ob);
void ts4200DIORefresh(ts4200DIO* ob);
void ts4200DIOCommit(ts4200DIO* ob,int ForceAll);
void ts4200DIOSet(ts4200DIO* ob,int DIONum,DIOState State);
DIOState ts4200DIOGet(ts4200DIO* ob,int DIONum);
void ts4200DIOSetAsync(ts4200DIO* ob,int DIONum,DIOState State);
DIOState ts4200DIOGetAsync(ts4200DIO* ob,int DIONum);
void ts4200DIOWait(ts4200DIO* ob,int *match,int min,int max,const int *nh,const int *nl);
unsigned ts4200DIOCount(ts4200DIO* ob);
DIOCaps ts4200DIOCapabilities(ts4200DIO* ob,unsigned num);
int ts4200DIOGetMulti(ts4200DIO* ob,char *state,int offset);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
