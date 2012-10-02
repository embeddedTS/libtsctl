#ifndef __WBSPI_H
#define __WBSPI_H
#include "SPI.h"
#include "Bus.h"

typedef struct WBSPI WBSPI;
struct WBSPI {
  SPI;
  Bus *bus,*bus8;
  int LockNum;
  int offset;
  void (*ChipSelect)(WBSPI *,unsigned num,int asserted);
};

void *WBSPIInit(WBSPI *,void *bus,void *bus8,int offset,void (*)(WBSPI *,unsigned,int));
void WBSPIFini(WBSPI *);
int WBSPILock(WBSPI *spi,unsigned num,int flags);
int WBSPIUnlock(WBSPI *spi,unsigned num,int flags);
void WBSPIPreempt(WBSPI *spi);
int WBSPIWrite(WBSPI *ob,int adrs,const char* buf);
int WBSPIRead(WBSPI *ob,int adrs,char *buf);
int WBSPIReadWrite(WBSPI *ob,int adrs,unsigned char* wbuf,unsigned char* rbuf);
int WBSPIClockSet(WBSPI *ob,unsigned hz);
int WBSPIEdgeSet(WBSPI *ob,int posedge);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
