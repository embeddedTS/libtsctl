#ifndef __SPI_h
#define __SPI_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct SPI SPI;
typedef enum SPIResult{
  SPISuccess=1,SPIErrorTimeout=-9,SPIErrorInvalidAddress=-10,SPIErrorInvalidEdge=-11,SPIErrorInvalidHz=-12
}SPIResult;

enum {
	NetSPI_Lock=0,
	NetSPI_Unlock=1,
	NetSPI_Preempt=2,
	NetSPI_Write=3,
	NetSPI_Read=4,
	NetSPI_ReadWrite=5,
	NetSPI_ClockSet=6,
	NetSPI_EdgeSet=7,
	XSPI_APICount=8
};
struct SPI {
	void *FUNC(Init)(void *me,...);
	void FUNC(Fini)(void *me);
	int FUNC(Lock)(void *me,unsigned num,int flags);
	int FUNC(Unlock)(void *me,unsigned num,int flags);
	int FUNC(Preempt)(void *me);
	SPIResult FUNC(Write)(void *me,int adrs,const unsigned char *buf);
	SPIResult FUNC(Read)(void *me,int adrs,unsigned char *buf);
	SPIResult FUNC(ReadWrite)(void *me,int adrs,const unsigned char *wbuf,unsigned char *rbuf);
	SPIResult FUNC(ClockSet)(void *me,unsigned hz);
	SPIResult FUNC(EdgeSet)(void *me,int posedge);
	int InitStatus;
};
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
