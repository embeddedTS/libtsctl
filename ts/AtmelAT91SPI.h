#ifndef __AtmelAT91SPI_H
#define __AtmelAT91SPI_H
#include "SPI.h"
#include "Bus.h"
#include "Pin.h"
#include "DIO.h"

typedef struct AtmelAT91SPI AtmelAT91SPI;
struct AtmelAT91SPI {
  SPI;
  Bus *bus;
  unsigned LockNum;
  Pin *pin;
  DIO *dio1,*dio2,*dio3;
  int cs1,cs2,cs3;
};

void *AtmelAT91SPIInit(AtmelAT91SPI *,void *bus,void *pin,
		       DIO *dio1,int cs1,DIO *dio2,int cs2,DIO *dio3,int cs3);
void AtmelAT91SPIFini(AtmelAT91SPI *);
int AtmelAT91SPILock(AtmelAT91SPI *spi,unsigned num,int flags);
int AtmelAT91SPIUnlock(AtmelAT91SPI *spi,unsigned num,int flags);
void AtmelAT91SPIPreempt(AtmelAT91SPI *spi);
int AtmelAT91SPIWrite(AtmelAT91SPI *ob,int adrs,const char* buf);
int AtmelAT91SPIRead(AtmelAT91SPI *ob,int adrs,char* buf);
int AtmelAT91SPIReadWrite(AtmelAT91SPI *ob,int adrs,const unsigned char* wbuf,unsigned char* rbuf);
int AtmelAT91SPIClockSet(AtmelAT91SPI *ob,unsigned hz);
int AtmelAT91SPIEdgeSet(AtmelAT91SPI *ob,int posedge);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
