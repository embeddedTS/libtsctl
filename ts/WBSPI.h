#ifndef __WBSPI_h
#define __WBSPI_h
#include "Bus.h"
#include "SPI.h"
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
	SPIResult FUNC(Write)(WBSPI *me,int adrs,const unsigned char *buf);
	SPIResult FUNC(Read)(WBSPI *me,int adrs,unsigned char *buf);
	SPIResult FUNC(ReadWrite)(WBSPI *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
	SPIResult FUNC(ClockSet)(WBSPI *me,unsigned hz);
	SPIResult FUNC(EdgeSet)(WBSPI *me,int posedge);
	int InitStatus;
	Bus *bus;
	Bus *bus8;
	int LockNum;
	int offset;
	void (*ChipSelect)(WBSPI *,unsigned num,int asserted);
       int use8;
};

void *WBSPIInit(WBSPI* ob,void *bus,void *bus8,int offset,void (*)(WBSPI *,unsigned ,int ));
void WBSPIFini(WBSPI* ob);
int WBSPILock(WBSPI* ob,unsigned num,int flags);
int WBSPIUnlock(WBSPI* ob,unsigned num,int flags);
int WBSPIPreempt(WBSPI* ob);
SPIResult WBSPIWrite(WBSPI* ob,int adrs,const unsigned char *buf);
SPIResult WBSPIRead(WBSPI* ob,int adrs,unsigned char *buf);
SPIResult WBSPIReadWrite(WBSPI* ob,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
SPIResult WBSPIClockSet(WBSPI* ob,unsigned hz);
SPIResult WBSPIEdgeSet(WBSPI* ob,int posedge);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
