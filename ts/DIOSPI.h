#ifndef __DIOSPI_h
#define __DIOSPI_h
#include "DIO.h"
#include "Time.h"
#include "SPI.h"
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct DIOSPI DIOSPI;
struct DIOSPI {
	void *FUNC(Init)(DIOSPI *me,DIO *cs0,DIO *cs1,DIO *cs2,DIO *cs3,int SPI_CS0,int SPI_CS1,int SPI_CS2,int SPI_CS3,DIO *mosi,int SPI_MOSI,DIO *miso,int SPI_MISO,DIO *clk,int SPI_CLK,Time *t);
	void FUNC(Fini)(DIOSPI *me);
	int FUNC(Lock)(DIOSPI *me,unsigned num,int flags);
	int FUNC(Unlock)(DIOSPI *me,unsigned num,int flags);
	int FUNC(Preempt)(DIOSPI *me);
	SPIResult FUNC(Write)(DIOSPI *me,int adrs,const unsigned char *buf);
	SPIResult FUNC(Read)(DIOSPI *me,int adrs,unsigned char *buf);
	SPIResult FUNC(ReadWrite)(DIOSPI *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
	SPIResult FUNC(ClockSet)(DIOSPI *me,unsigned hz);
	SPIResult FUNC(EdgeSet)(DIOSPI *me,int posedge);
	int InitStatus;
	DIO *cs[4];
	int SPI_CS[4];
	DIO *mosi;
	int SPI_MOSI;
	DIO *miso;
	int SPI_MISO;
	DIO *clk;
	int SPI_CLK;
	int CPOL;
	int CPHA;
	Time *t;
	unsigned delay;
};

void *DIOSPIInit(DIOSPI* ob,DIO *cs0,DIO *cs1,DIO *cs2,DIO *cs3,int SPI_CS0,int SPI_CS1,int SPI_CS2,int SPI_CS3,DIO *mosi,int SPI_MOSI,DIO *miso,int SPI_MISO,DIO *clk,int SPI_CLK,Time *t);
void DIOSPIFini(DIOSPI* ob);
int DIOSPILock(DIOSPI* ob,unsigned num,int flags);
int DIOSPIUnlock(DIOSPI* ob,unsigned num,int flags);
int DIOSPIPreempt(DIOSPI* ob);
SPIResult DIOSPIWrite(DIOSPI* ob,int adrs,const unsigned char *buf);
SPIResult DIOSPIRead(DIOSPI* ob,int adrs,unsigned char *buf);
SPIResult DIOSPIReadWrite(DIOSPI* ob,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
SPIResult DIOSPIClockSet(DIOSPI* ob,unsigned hz);
SPIResult DIOSPIEdgeSet(DIOSPI* ob,int posedge);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
