#ifndef __WBWindowBus_h
#define __WBWindowBus_h
#include "Bus.h"

typedef struct WBWindowBus WBWindowBus;

struct WBWindowBus {
  Bus;
  Bus *sub; // bus containing the window registers
  int adrs; // offset address of window
  int offset; // starting offset within the window
};

void *WBWindowBusInit(WBWindowBus *,void *bus,int adrs,int offset);
void WBWindowBusFini(WBWindowBus *);
int WBWindowBusLock(WBWindowBus *bus,unsigned num,int flags);
int WBWindowBusUnlock(WBWindowBus *bus,unsigned num,int flags);
int WBWindowBusPreempt(WBWindowBus *bus);

unsigned char WBWindowBusPeek8(WBWindowBus *,int adrs);
void WBWindowBusPoke8(WBWindowBus *,int adrs,unsigned char val);
unsigned short WBWindowBusPeek16(WBWindowBus *,int adrs);
void WBWindowBusPoke16(WBWindowBus *,int adrs,unsigned short val);
unsigned WBWindowBusPeek32(WBWindowBus *,int adrs);
void WBWindowBusPoke32(WBWindowBus *,int adrs,unsigned val);
int WBWindowBusBitGet8(WBWindowBus *bus,int adrs,int bit);
void WBWindowBusBitAssign8(WBWindowBus *bus,int adrs,int bit,int val);
void WBWindowBusBitSet8(WBWindowBus *bus,int adrs,int bit);
void WBWindowBusBitClear8(WBWindowBus *bus,int adrs,int bit);
int WBWindowBusBitGet16(WBWindowBus *bus,int adrs,int bit);
void WBWindowBusBitAssign16(WBWindowBus *bus,int adrs,int bit,int val);
void WBWindowBusBitSet16(WBWindowBus *bus,int adrs,int bit);
void WBWindowBusBitClear16(WBWindowBus *bus,int adrs,int bit);
int WBWindowBusBitGet32(WBWindowBus *bus,int adrs,int bit);
void WBWindowBusBitAssign32(WBWindowBus *bus,int adrs,int bit,int val);
void WBWindowBusBitSet32(WBWindowBus *bus,int adrs,int bit);
void WBWindowBusBitClear32(WBWindowBus *bus,int adrs,int bit);
void WBWindowBusPeekStream(WBWindowBus *bus,int adr,int dir,char* buf);
void WBWindowBusPokeStream(WBWindowBus *bus,int adr,int dir,const char* buf);
void WBWindowBusRefresh(WBWindowBus *);
void WBWindowBusCommit(WBWindowBus *,int forceall);
int WBWindowBusBitToggle8(WBWindowBus *bus,int adrs,int bit);
int WBWindowBusBitToggle16(WBWindowBus *bus,int adrs,int bit);
int WBWindowBusBitToggle32(WBWindowBus *bus,int adrs,int bit);
unsigned char WBWindowBusAssign8X(WBWindowBus *,int adrs,int bit1,int bit0,int val);
unsigned short WBWindowBusAssign16X(WBWindowBus *,int adrs,int bit1,int bit0,int val);
unsigned WBWindowBusAssign32X(WBWindowBus *,int adrs,int bit1,int bit0,int val);
unsigned char WBWindowBusBitsGet8(WBWindowBus *,int adrs,int bit1,int bit0);
unsigned short WBWindowBusBitsGet16(WBWindowBus *,int adrs,int bit1,int bit0);
unsigned WBWindowBusBitsGet32(WBWindowBus *,int adrs,int bit1,int bit0);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
