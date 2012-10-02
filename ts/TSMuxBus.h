#ifndef __TSMuxBus_h
#define __TSMuxBus_h
#include "Bus.h"

typedef struct TSMuxBus TSMuxBus;

struct TSMuxBus {
  Bus;
  Bus *configbus, *regbus8, *regbus16;
  int cadrs,base8,base16;
};

void *TSMuxBusInit(TSMuxBus *,void *configbus,int cadrs,void *regbus8, int base8, void *regbus16, int base16);
void TSMuxBusFini(TSMuxBus *);
unsigned char TSMuxBusPeek8(TSMuxBus *,int adrs);
void TSMuxBusPoke8(TSMuxBus *,int adrs,unsigned char val);
unsigned short TSMuxBusPeek16(TSMuxBus *,int adrs);
void TSMuxBusPoke16(TSMuxBus *,int adrs,unsigned short val);
unsigned TSMuxBusPeek32(TSMuxBus *,int adrs);
void TSMuxBusPoke32(TSMuxBus *,int adrs,unsigned val);
int TSMuxBusBitGet8(TSMuxBus *bus,int adrs,int bit);
void TSMuxBusBitAssign8(TSMuxBus *bus,int adrs,int bit,int val);
void TSMuxBusBitSet8(TSMuxBus *bus,int adrs,int bit);
void TSMuxBusBitClear8(TSMuxBus *bus,int adrs,int bit);
int TSMuxBusBitGet16(TSMuxBus *bus,int adrs,int bit);
void TSMuxBusBitAssign16(TSMuxBus *bus,int adrs,int bit,int val);
void TSMuxBusBitSet16(TSMuxBus *bus,int adrs,int bit);
void TSMuxBusBitClear16(TSMuxBus *bus,int adrs,int bit);
int TSMuxBusBitGet32(TSMuxBus *bus,int adrs,int bit);
void TSMuxBusBitAssign32(TSMuxBus *bus,int adrs,int bit,int val);
void TSMuxBusBitSet32(TSMuxBus *bus,int adrs,int bit);
void TSMuxBusBitClear32(TSMuxBus *bus,int adrs,int bit);
void TSMuxBusPeekStream(TSMuxBus *bus,int adr,int dir,char* buf);
void TSMuxBusPokeStream(TSMuxBus *bus,int adr,int dir,const char* buf);
void TSMuxBusRefresh(TSMuxBus *);
void TSMuxBusCommit(TSMuxBus *,int forceall);
int TSMuxBusBitToggle8(TSMuxBus *bus,int adrs,int bit);
int TSMuxBusBitToggle16(TSMuxBus *bus,int adrs,int bit);
int TSMuxBusBitToggle32(TSMuxBus *bus,int adrs,int bit);
unsigned char TSMuxBusAssign8X(TSMuxBus *,int adrs,int bit1,int bit0,int val);
unsigned short TSMuxBusAssign16X(TSMuxBus *,int adrs,int bit1,int bit0,int val);
unsigned TSMuxBusAssign32X(TSMuxBus *,int adrs,int bit1,int bit0,int val);
unsigned char TSMuxBusBitsGet8(TSMuxBus *,int adrs,int bit1,int bit0);
unsigned short TSMuxBusBitsGet16(TSMuxBus *,int adrs,int bit1,int bit0);
unsigned TSMuxBusBitsGet32(TSMuxBus *,int adrs,int bit1,int bit0);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
