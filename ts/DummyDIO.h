#ifndef __DummyDIO_h
#define __DummyDIO_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct DummyDIO DummyDIO;
struct DummyDIO {
	void *FUNC(Init)(DummyDIO *me,int count);
	void FUNC(Fini)(DummyDIO *me);
	int FUNC(Lock)(DummyDIO *me,unsigned num,int flags);
	int FUNC(Unlock)(DummyDIO *me,unsigned num,int flags);
	int FUNC(Preempt)(DummyDIO *me);
	void FUNC(Refresh)(DummyDIO *me);
	void FUNC(Commit)(DummyDIO *me,int ForceAll);
	void FUNC(Set)(DummyDIO *me,int DIONum,DIOState State);
	DIOState FUNC(Get)(DummyDIO *me,int DIONum);
	void FUNC(SetAsync)(DummyDIO *me,int DIONum,DIOState State);
	DIOState FUNC(GetAsync)(DummyDIO *me,int DIONum);
	void FUNC(Wait)(DummyDIO *me,int *match,int min,int max,const int *nh,const int *nl);
	unsigned FUNC(Count)(DummyDIO *me);
	DIOCaps FUNC(Capabilities)(DummyDIO *me,unsigned num);
	int FUNC(GetMulti)(DummyDIO *me,char *state,int offset);
	int InitStatus;
	unsigned NumLocks;
};

void *DummyDIOInit(DummyDIO* ob,int count);
void DummyDIOFini(DummyDIO* ob);
int DummyDIOLock(DummyDIO* ob,unsigned num,int flags);
int DummyDIOUnlock(DummyDIO* ob,unsigned num,int flags);
int DummyDIOPreempt(DummyDIO* ob);
void DummyDIORefresh(DummyDIO* ob);
void DummyDIOCommit(DummyDIO* ob,int ForceAll);
void DummyDIOSet(DummyDIO* ob,int DIONum,DIOState State);
DIOState DummyDIOGet(DummyDIO* ob,int DIONum);
void DummyDIOSetAsync(DummyDIO* ob,int DIONum,DIOState State);
DIOState DummyDIOGetAsync(DummyDIO* ob,int DIONum);
void DummyDIOWait(DummyDIO* ob,int *match,int min,int max,const int *nh,const int *nl);
unsigned DummyDIOCount(DummyDIO* ob);
DIOCaps DummyDIOCapabilities(DummyDIO* ob,unsigned num);
int DummyDIOGetMulti(DummyDIO* ob,char *state,int offset);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
