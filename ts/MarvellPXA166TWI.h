#ifndef __MarvellPXA166TWI_h
#define __MarvellPXA166TWI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct MarvellPXA166TWI MarvellPXA166TWI;
struct MarvellPXA166TWI {
	void *FUNC(Init)(MarvellPXA166TWI *me,void *bus);
	void FUNC(Fini)(MarvellPXA166TWI *me);
	int FUNC(Lock)(MarvellPXA166TWI *me,unsigned num,int flags);
	int FUNC(Unlock)(MarvellPXA166TWI *me,unsigned num,int flags);
	int FUNC(Preempt)(MarvellPXA166TWI *me);
	TWIResult FUNC(Write)(MarvellPXA166TWI *me,int devadr,int adrslen,int adrs,const char *bytes);
	TWIResult FUNC(Read)(MarvellPXA166TWI *me,int devadr,int adrslen,int adrs,char *bytes);
	int InitStatus;
	Bus *bus;
	int LockNum;
};

void *MarvellPXA166TWIInit(MarvellPXA166TWI* ob,void *bus);
void MarvellPXA166TWIFini(MarvellPXA166TWI* ob);
int MarvellPXA166TWILock(MarvellPXA166TWI* ob,unsigned num,int flags);
int MarvellPXA166TWIUnlock(MarvellPXA166TWI* ob,unsigned num,int flags);
int MarvellPXA166TWIPreempt(MarvellPXA166TWI* ob);
TWIResult MarvellPXA166TWIWrite(MarvellPXA166TWI* ob,int devadr,int adrslen,int adrs,const char *bytes);
TWIResult MarvellPXA166TWIRead(MarvellPXA166TWI* ob,int devadr,int adrslen,int adrs,char *bytes);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
