#ifndef __WBSPI_h
#define __WBSPI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct WBSPI WBSPI;
struct WBSPI {
	void *FUNC(Init)(WBSPI *me,void *bus,void *bus8,int offset,void (*)(WBSPI *,unsigned ,int ));
	void FUNC(Fini)(WBSPI *me);
	int FUNC(Lock)(WBSPI *me,unsigned num,int flags);
	int FUNC(Unlock)(WBSPI *me,unsigned num,int flags);
	int FUNC(Preempt)(WBSPI *me);
	int FUNC(Write)(WBSPI *me,int adrs,const unsigned char *buf);
	int FUNC(Read)(WBSPI *me,int adrs,unsigned char *buf);
	int FUNC(ReadWrite)(WBSPI *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
	int FUNC(ClockSet)(WBSPI *me,unsigned hz);
	int FUNC(EdgeSet)(WBSPI *me,int posedge);
	int InitStatus;
	Bus *bus;
	Bus *bus8;
	int LockNum;
	int offset;
	void (*ChipSelect)(WBSPI *,unsigned num,int asserted);
};

void *WBSPIInit(WBSPI* ob,void *bus,void *bus8,int offset,void (*)(WBSPI *,unsigned ,int ));
void WBSPIFini(WBSPI* ob);
int WBSPILock(WBSPI* ob,unsigned num,int flags);
int WBSPIUnlock(WBSPI* ob,unsigned num,int flags);
int WBSPIPreempt(WBSPI* ob);
int WBSPIWrite(WBSPI* ob,int adrs,const unsigned char *buf);
int WBSPIRead(WBSPI* ob,int adrs,unsigned char *buf);
int WBSPIReadWrite(WBSPI* ob,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
int WBSPIClockSet(WBSPI* ob,unsigned hz);
int WBSPIEdgeSet(WBSPI* ob,int posedge);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
