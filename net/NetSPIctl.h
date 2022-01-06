#ifndef __NetSPIctl_H
#define __NetSPIctl_H
#include "Net.h"
#include "SPI.h"
typedef struct NetSPIctl NetSPIctl;

struct NetSPIctl {
  SPIAPI;
  int InitStatus;
  int inst;
  int socket;
  int edge;
};

#define CS_DO_ASSERT 3
#define CS_DO_DEASSERT 1
#define CS_DO_NOTHING 0
#define EDGE_DO_POS 3
#define EDGE_DO_NEG 2
#define EDGE_DO_NOTHING 0
#define SPICMD_READ 1
#define SPICMD_READWRITE 3
#define SPICMD_WRITE 2

/*
spictl format:
1. CS
U8 COMMAND
U16 CLOCK
=>
N/A

2. READ
U8 COMMAND
=>
U8[request_length] DATA

3. WRITE
U8 COMMAND
U8[request_length] DATA
=>
N/A

4. READWRITE
U8 COMMAND
U8[request_length] DATA
=>
U8[request_length] DATA

BYTE command_info

 */
void *NetSPIctlInit(NetSPIctl *,int socket,int inst);
void NetSPIctlFini(NetSPIctl *);
int NetSPIctlLock(NetSPIctl *,int,unsigned);
int NetSPIctlWrite(NetSPIctl *spi,int adrs,unsigned char *buf,int len);
int NetSPIctlRead(NetSPIctl *spi,int adrs,unsigned char *buf,int len);
int NetSPIctlReadWrite(NetSPIctl *spi,int adrs,unsigned char *wbuf,unsigned char *rbuf, int len);
int NetSPIctlClockSet(NetSPIctl *spi,unsigned hz);
int NetSPIctlEdgeSet(NetSPIctl *spi,int posedge);


#endif
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
