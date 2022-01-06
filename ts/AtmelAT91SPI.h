#ifndef __AtmelAT91SPI_h
#define __AtmelAT91SPI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct AtmelAT91SPI AtmelAT91SPI;
struct AtmelAT91SPI {
	void *FUNC(Init)(AtmelAT91SPI *me,void *bus,void *pin,DIO *dio1,int cs1,DIO *dio2,int cs2,DIO *dio3,int cs3);
	void FUNC(Fini)(AtmelAT91SPI *me);
	int FUNC(Lock)(AtmelAT91SPI *me,unsigned num,int flags);
	int FUNC(Unlock)(AtmelAT91SPI *me,unsigned num,int flags);
	int FUNC(Preempt)(AtmelAT91SPI *me);
	SPIResult FUNC(Write)(AtmelAT91SPI *me,int adrs,const unsigned char *buf);
	SPIResult FUNC(Read)(AtmelAT91SPI *me,int adrs,unsigned char *buf);
	SPIResult FUNC(ReadWrite)(AtmelAT91SPI *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
	SPIResult FUNC(ClockSet)(AtmelAT91SPI *me,unsigned hz);
	SPIResult FUNC(EdgeSet)(AtmelAT91SPI *me,int posedge);
	int InitStatus;
	Bus *bus;
	unsigned LockNum;
	Pin *pin;
	DIO *dio1;
	DIO *dio2;
	DIO *dio3;
	int cs1;
	int cs2;
	int cs3;
};

void *AtmelAT91SPIInit(AtmelAT91SPI* ob,void *bus,void *pin,DIO *dio1,int cs1,DIO *dio2,int cs2,DIO *dio3,int cs3);
void AtmelAT91SPIFini(AtmelAT91SPI* ob);
int AtmelAT91SPILock(AtmelAT91SPI* ob,unsigned num,int flags);
int AtmelAT91SPIUnlock(AtmelAT91SPI* ob,unsigned num,int flags);
int AtmelAT91SPIPreempt(AtmelAT91SPI* ob);
SPIResult AtmelAT91SPIWrite(AtmelAT91SPI* ob,int adrs,const unsigned char *buf);
SPIResult AtmelAT91SPIRead(AtmelAT91SPI* ob,int adrs,unsigned char *buf);
SPIResult AtmelAT91SPIReadWrite(AtmelAT91SPI* ob,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
SPIResult AtmelAT91SPIClockSet(AtmelAT91SPI* ob,unsigned hz);
SPIResult AtmelAT91SPIEdgeSet(AtmelAT91SPI* ob,int posedge);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
