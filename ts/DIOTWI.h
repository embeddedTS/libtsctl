#ifndef __DIOTWI_h
#define __DIOTWI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct DIOTWI DIOTWI;
struct DIOTWI {
	void *FUNC(Init)(DIOTWI *me,void *dio,void *time);
	void FUNC(Fini)(DIOTWI *me);
	int FUNC(Lock)(DIOTWI *me,unsigned num,int flags);
	int FUNC(Unlock)(DIOTWI *me,unsigned num,int flags);
	int FUNC(Preempt)(DIOTWI *me);
	TWIResult FUNC(Write)(DIOTWI *me,int devadr,int adrslen,int adrs,const char *bytes);
	TWIResult FUNC(Read)(DIOTWI *me,int devadr,int adrslen,int adrs,char *bytes);
	int InitStatus;
	DIO *dio;
	Time *t;
	int TW_CLK;
	int TW_DAT;
	int Speed;
	int delay;
	int LockNum;
	unsigned start;
};

void *DIOTWIInit(DIOTWI* ob,void *dio,void *time);
void DIOTWIFini(DIOTWI* ob);
int DIOTWILock(DIOTWI* ob,unsigned num,int flags);
int DIOTWIUnlock(DIOTWI* ob,unsigned num,int flags);
int DIOTWIPreempt(DIOTWI* ob);
TWIResult DIOTWIWrite(DIOTWI* ob,int devadr,int adrslen,int adrs,const char *bytes);
TWIResult DIOTWIRead(DIOTWI* ob,int devadr,int adrslen,int adrs,char *bytes);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
