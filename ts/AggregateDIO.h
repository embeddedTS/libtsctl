#ifndef __AggregateDIO_h
#define __AggregateDIO_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct AggregateDIO AggregateDIO;
struct AggregateDIO {
	void *FUNC(Init)(AggregateDIO *me,unsigned Count,void *pin,int *SubCount,DIO **pDIO);
	void FUNC(Fini)(AggregateDIO *me);
	int FUNC(Lock)(AggregateDIO *me,unsigned num,int flags);
	int FUNC(Unlock)(AggregateDIO *me,unsigned num,int flags);
	int FUNC(Preempt)(AggregateDIO *me);
	void FUNC(Refresh)(AggregateDIO *me);
	void FUNC(Commit)(AggregateDIO *me,int forceall);
	void FUNC(Set)(AggregateDIO *me,int DIONum,DIOState State);
	DIOState FUNC(Get)(AggregateDIO *me,int DIONum);
	void FUNC(SetAsync)(AggregateDIO *me,int DIONum,DIOState State);
	DIOState FUNC(GetAsync)(AggregateDIO *me,int DIONum);
	void FUNC(Wait)(AggregateDIO *me,int *match,int min,int max,const int *nh,const int *nl);
	unsigned FUNC(Count)(AggregateDIO *me);
	DIOCaps FUNC(Capabilities)(AggregateDIO *me,unsigned num);
	int FUNC(GetMulti)(AggregateDIO *me,char *,int offset);
	int InitStatus;
	DIO **dio;
	Pin *pin;
	int nCount;
	int *SubCount;
};

void *AggregateDIOInit(AggregateDIO* ob,unsigned Count,void *pin,int *SubCount,DIO **pDIO);
void AggregateDIOFini(AggregateDIO* ob);
int AggregateDIOLock(AggregateDIO* ob,unsigned num,int flags);
int AggregateDIOUnlock(AggregateDIO* ob,unsigned num,int flags);
int AggregateDIOPreempt(AggregateDIO* ob);
void AggregateDIORefresh(AggregateDIO* ob);
void AggregateDIOCommit(AggregateDIO* ob,int forceall);
void AggregateDIOSet(AggregateDIO* ob,int DIONum,DIOState State);
DIOState AggregateDIOGet(AggregateDIO* ob,int DIONum);
void AggregateDIOSetAsync(AggregateDIO* ob,int DIONum,DIOState State);
DIOState AggregateDIOGetAsync(AggregateDIO* ob,int DIONum);
void AggregateDIOWait(AggregateDIO* ob,int *match,int min,int max,const int *nh,const int *nl);
unsigned AggregateDIOCount(AggregateDIO* ob);
DIOCaps AggregateDIOCapabilities(AggregateDIO* ob,unsigned num);
int AggregateDIOGetMulti(AggregateDIO* ob,char *,int offset);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
