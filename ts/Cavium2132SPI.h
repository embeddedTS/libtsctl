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
	int FUNC(Write)(Cavium2132SPI *me,int adrs,const unsigned char *buf);
	int FUNC(Read)(Cavium2132SPI *me,int adrs,unsigned char *buf);
	int FUNC(ReadWrite)(Cavium2132SPI *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
	int FUNC(ClockSet)(Cavium2132SPI *me,unsigned hz);
	int FUNC(EdgeSet)(Cavium2132SPI *me,int posedge);
	int InitStatus;
	Bus *bus;
	int LockNum;
};

void *Cavium2132SPIInit(Cavium2132SPI* ob,void *bus);
void Cavium2132SPIFini(Cavium2132SPI* ob);
int Cavium2132SPILock(Cavium2132SPI* ob,unsigned num,int flags);
int Cavium2132SPIUnlock(Cavium2132SPI* ob,unsigned num,int flags);
int Cavium2132SPIPreempt(Cavium2132SPI* ob);
int Cavium2132SPIWrite(Cavium2132SPI* ob,int adrs,const unsigned char *buf);
int Cavium2132SPIRead(Cavium2132SPI* ob,int adrs,unsigned char *buf);
int Cavium2132SPIReadWrite(Cavium2132SPI* ob,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
int Cavium2132SPIClockSet(Cavium2132SPI* ob,unsigned hz);
int Cavium2132SPIEdgeSet(Cavium2132SPI* ob,int posedge);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
