#ifndef __FreescaleIMX51TWI_h
#define __FreescaleIMX51TWI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct FreescaleIMX51TWI FreescaleIMX51TWI;
struct FreescaleIMX51TWI {
	void *FUNC(Init)(FreescaleIMX51TWI *me,void *bus);
	void FUNC(Fini)(FreescaleIMX51TWI *me);
	int FUNC(Lock)(FreescaleIMX51TWI *me,unsigned num,int flags);
	int FUNC(Unlock)(FreescaleIMX51TWI *me,unsigned num,int flags);
	int FUNC(Preempt)(FreescaleIMX51TWI *me);
	TWIResult FUNC(Write)(FreescaleIMX51TWI *me,int devadr,int adrslen,int adrs,const char *bytes);
	TWIResult FUNC(Read)(FreescaleIMX51TWI *me,int devadr,int adrslen,int adrs,char *bytes);
	int InitStatus;
	Bus *bus;
	int LockNum;
};

void *FreescaleIMX51TWIInit(FreescaleIMX51TWI* ob,void *bus);
void FreescaleIMX51TWIFini(FreescaleIMX51TWI* ob);
int FreescaleIMX51TWILock(FreescaleIMX51TWI* ob,unsigned num,int flags);
int FreescaleIMX51TWIUnlock(FreescaleIMX51TWI* ob,unsigned num,int flags);
int FreescaleIMX51TWIPreempt(FreescaleIMX51TWI* ob);
TWIResult FreescaleIMX51TWIWrite(FreescaleIMX51TWI* ob,int devadr,int adrslen,int adrs,const char *bytes);
TWIResult FreescaleIMX51TWIRead(FreescaleIMX51TWI* ob,int devadr,int adrslen,int adrs,char *bytes);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
