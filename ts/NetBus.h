#ifndef __NetBus_h
#define __NetBus_h
#include "Net.h"
#include "Bus.h"
#include <stdio.h>
#include "Packet.h"

typedef struct NetBus NetBus;


// 2. we must init the packet in Init and DoCmd*, not individual functions
// fix PeekStream, DoCmd isn't compatible with it
struct NetBus {
  Bus;
  int inst;
  int socket;
  int mode;
  Packet *q;
  int *cmds;
};

void *NetBusInit(NetBus *,int socket,int inst,int mode,Packet *q,int *cmds);
void NetBusFini(NetBus *);
int NetBusLock(NetBus *,int,unsigned);
unsigned char NetBusPeek8(NetBus *,int adrs);
void NetBusPoke8(NetBus *,int adrs,unsigned char val);
unsigned short NetBusPeek16(NetBus *,int adrs);
void NetBusPoke16(NetBus *,int adrs,unsigned short val);
unsigned NetBusPeek32(NetBus *,int adrs);
void NetBusPoke32(NetBus *,int adrs,unsigned val);
int NetBusBitGet8(NetBus *bus,int adrs,int bit);
void NetBusBitAssign8(NetBus *bus,int adrs,int bit,int val);
void NetBusBitSet8(NetBus *bus,int adrs,int bit);
void NetBusBitClear8(NetBus *bus,int adrs,int bit);
int NetBusBitGet16(NetBus *bus,int adrs,int bit);
void NetBusBitAssign16(NetBus *bus,int adrs,int bit,int val);
void NetBusBitSet16(NetBus *bus,int adrs,int bit);
void NetBusBitClear16(NetBus *bus,int adrs,int bit);
int NetBusBitGet32(NetBus *bus,int adrs,int bit);
void NetBusBitAssign32(NetBus *bus,int adrs,int bit,int val);
void NetBusBitSet32(NetBus *bus,int adrs,int bit);
void NetBusBitClear32(NetBus *bus,int adrs,int bit);
void NetBusPeekStream(NetBus *bus,int adr,int dir,char *buf,int len);
void NetBusPokeStream(NetBus *bus,int adr,int dir,char *buf,int len);
void NetBusRefresh(NetBus *);
void NetBusCommit(NetBus *,int forceall);
int NetBusBitToggle8(NetBus *bus,int adrs,int bit);
int NetBusBitToggle16(NetBus *bus,int adrs,int bit);
int NetBusBitToggle32(NetBus *bus,int adrs,int bit);
unsigned char NetBusAssign8X(NetBus *,int adrs,int bit1,int bit0,int val);
unsigned short NetBusAssign16X(NetBus *,int adrs,int bit1,int bit0,int val);
unsigned NetBusAssign32X(NetBus *,int adrs,int bit1,int bit0,int val);
unsigned char NetBusBitsGet8(NetBus *,int adrs,int bit1,int bit0);
unsigned short NetBusBitsGet16(NetBus *,int adrs,int bit1,int bit0);
unsigned NetBusBitsGet32(NetBus *,int adrs,int bit1,int bit0);

enum {
  MapBusErrorServer=-100
};

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
