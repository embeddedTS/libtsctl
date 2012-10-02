#ifndef __NetSPI_H
#define __NetSPI_H
#include "Net.h"
#include "SPI.h"
typedef struct NetSPI NetSPI;

struct NetSPI {
  SPIAPI;
  int InitStatus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetSPIInit(NetSPI *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetSPIFini(NetSPI *);
int NetSPILock(NetSPI *,int,unsigned);
int NetSPIWrite(NetSPI *spi,int adrs,unsigned char *buf,int len);
int NetSPIRead(NetSPI *spi,int adrs,unsigned char *buf,int len);
int NetSPIReadWrite(NetSPI *spi,int adrs,unsigned char *wbuf,unsigned char *rbuf, int len);
int NetSPIClockSet(NetSPI *spi,unsigned hz);
int NetSPIEdgeSet(NetSPI *spi,int posedge);


#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
