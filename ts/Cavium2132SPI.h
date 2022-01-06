#ifndef __Cavium2132SPI_h
#define __Cavium2132SPI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct Cavium2132SPI Cavium2132SPI;
struct Cavium2132SPI {
	void *FUNC(Init)(Cavium2132SPI *me,void *bus);
	void FUNC(Fini)(Cavium2132SPI *me);
	int FUNC(Lock)(Cavium2132SPI *me,unsigned num,int flags);
	int FUNC(Unlock)(Cavium2132SPI *me,unsigned num,int flags);
	int FUNC(Preempt)(Cavium2132SPI *me);
	SPIResult FUNC(Write)(Cavium2132SPI *me,int adrs,const unsigned char *buf);
	SPIResult FUNC(Read)(Cavium2132SPI *me,int adrs,unsigned char *buf);
	SPIResult FUNC(ReadWrite)(Cavium2132SPI *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
	SPIResult FUNC(ClockSet)(Cavium2132SPI *me,unsigned hz);
	SPIResult FUNC(EdgeSet)(Cavium2132SPI *me,int posedge);
	int InitStatus;
	Bus *bus;
	int LockNum;
};

void *Cavium2132SPIInit(Cavium2132SPI* ob,void *bus);
void Cavium2132SPIFini(Cavium2132SPI* ob);
int Cavium2132SPILock(Cavium2132SPI* ob,unsigned num,int flags);
int Cavium2132SPIUnlock(Cavium2132SPI* ob,unsigned num,int flags);
int Cavium2132SPIPreempt(Cavium2132SPI* ob);
SPIResult Cavium2132SPIWrite(Cavium2132SPI* ob,int adrs,const unsigned char *buf);
SPIResult Cavium2132SPIRead(Cavium2132SPI* ob,int adrs,unsigned char *buf);
SPIResult Cavium2132SPIReadWrite(Cavium2132SPI* ob,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
SPIResult Cavium2132SPIClockSet(Cavium2132SPI* ob,unsigned hz);
SPIResult Cavium2132SPIEdgeSet(Cavium2132SPI* ob,int posedge);
#endif

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
