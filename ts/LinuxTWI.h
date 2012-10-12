#ifndef __LinuxTWI_h
#define __LinuxTWI_h
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
	int FUNC(Write)(LinuxTWI *me,int devadr,int adrslen,int adrs,const char *bytes);
	int FUNC(Read)(LinuxTWI *me,int devadr,int adrslen,int adrs,char *bytes);
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
int LinuxTWIWrite(LinuxTWI* ob,int devadr,int adrslen,int adrs,const char *bytes);
int LinuxTWIRead(LinuxTWI* ob,int devadr,int adrslen,int adrs,char *bytes);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
