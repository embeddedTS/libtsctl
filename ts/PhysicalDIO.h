#ifndef __PhysicalDIO_h
#define __PhysicalDIO_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct PhysicalDIO PhysicalDIO;
struct PhysicalDIO {
	void *FUNC(Init)(PhysicalDIO *me,void *bus,void *dio);
	void FUNC(Fini)(PhysicalDIO *me);
	int FUNC(Lock)(PhysicalDIO *me,unsigned num,int flags);
	int FUNC(Unlock)(PhysicalDIO *me,unsigned num,int flags);
	int FUNC(Preempt)(PhysicalDIO *me);
	void FUNC(Refresh)(PhysicalDIO *me);
	void FUNC(Commit)(PhysicalDIO *me,int ForceAll);
	void FUNC(Set)(PhysicalDIO *me,int DIONum,DIOState State);
	DIOState FUNC(Get)(PhysicalDIO *me,int DIONum);
	void FUNC(SetAsync)(PhysicalDIO *me,int DIONum,DIOState State);
	DIOState FUNC(GetAsync)(PhysicalDIO *me,int DIONum);
	void FUNC(Wait)(PhysicalDIO *me,int *match,int min,int max,const int *nh,const int *nl);
	unsigned FUNC(Count)(PhysicalDIO *me);
	DIOCaps FUNC(Capabilities)(PhysicalDIO *me,unsigned num);
	int FUNC(GetMulti)(PhysicalDIO *me,char *state,int offset);
	int InitStatus;
	unsigned NumLocks;
	Bus *bus;
	DIORaw *dio;
	int gotHUP;
	unsigned char *Caps;
	int *dirCache;
};

void *PhysicalDIOInit(PhysicalDIO* ob,void *bus,void *dio);
void PhysicalDIOFini(PhysicalDIO* ob);
int PhysicalDIOLock(PhysicalDIO* ob,unsigned num,int flags);
int PhysicalDIOUnlock(PhysicalDIO* ob,unsigned num,int flags);
int PhysicalDIOPreempt(PhysicalDIO* ob);
void PhysicalDIORefresh(PhysicalDIO* ob);
void PhysicalDIOCommit(PhysicalDIO* ob,int ForceAll);
void PhysicalDIOSet(PhysicalDIO* ob,int DIONum,DIOState State);
DIOState PhysicalDIOGet(PhysicalDIO* ob,int DIONum);
void PhysicalDIOSetAsync(PhysicalDIO* ob,int DIONum,DIOState State);
DIOState PhysicalDIOGetAsync(PhysicalDIO* ob,int DIONum);
void PhysicalDIOWait(PhysicalDIO* ob,int *match,int min,int max,const int *nh,const int *nl);
unsigned PhysicalDIOCount(PhysicalDIO* ob);
DIOCaps PhysicalDIOCapabilities(PhysicalDIO* ob,unsigned num);
int PhysicalDIOGetMulti(PhysicalDIO* ob,char *state,int offset);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
