#ifndef __Cavium2132SPI_H
#define __Cavium2132SPI_H
#include "SPI.h"
#include "Bus.h"
#include "Lock.h"

typedef struct Cavium2132SPI Cavium2132SPI;
struct Cavium2132SPI {
  SPI;
  Bus *bus;
  int LockNum;
};

void *Cavium2132SPIInit(Cavium2132SPI *,void *bus);
void Cavium2132SPIFini(Cavium2132SPI *);
int Cavium2132SPILock(Cavium2132SPI *,int command,unsigned num);
int Cavium2132SPIWrite(Cavium2132SPI *ob,int adrs,char *buf,int len);
int Cavium2132SPIRead(Cavium2132SPI *ob,int adrs,char *buf,int len);
int Cavium2132SPIReadWrite(Cavium2132SPI *ob,int adrs,unsigned char *wbuf,unsigned char *rbuf, int len);
int Cavium2132SPIClockSet(Cavium2132SPI *ob,unsigned hz);
int Cavium2132SPIEdgeSet(Cavium2132SPI *ob,int posedge);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
