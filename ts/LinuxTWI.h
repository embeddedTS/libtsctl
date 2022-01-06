#ifndef __LinuxTWI_h
#define __LinuxTWI_h
#include "TWI.h"
#include "Bus.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct LinuxTWI LinuxTWI;
struct LinuxTWI {
	void *FUNC(Init)(LinuxTWI *me,char *devfile);
	void FUNC(Fini)(LinuxTWI *me);
	int FUNC(Lock)(LinuxTWI *me,unsigned num,int flags);
	int FUNC(Unlock)(LinuxTWI *me,unsigned num,int flags);
	int FUNC(Preempt)(LinuxTWI *me);
	TWIResult FUNC(Write)(LinuxTWI *me,int devadr,int adrslen,int adrs,const char *bytes);
	TWIResult FUNC(Read)(LinuxTWI *me,int devadr,int adrslen,int adrs,char *bytes);
	int InitStatus;
	Bus *bus;
	int LockNum;
	char *devfile;
	int f;
};

void *LinuxTWIInit(LinuxTWI* ob,char *devfile);
void LinuxTWIFini(LinuxTWI* ob);
int LinuxTWILock(LinuxTWI* ob,unsigned num,int flags);
int LinuxTWIUnlock(LinuxTWI* ob,unsigned num,int flags);
int LinuxTWIPreempt(LinuxTWI* ob);
TWIResult LinuxTWIWrite(LinuxTWI* ob,int devadr,int adrslen,int adrs,const char *bytes);
TWIResult LinuxTWIRead(LinuxTWI* ob,int devadr,int adrslen,int adrs,char *bytes);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
