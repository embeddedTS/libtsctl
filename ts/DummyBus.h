#ifndef __DummyBus_h
#define __DummyBus_h
#include "Bus.h"

typedef struct DummyBus DummyBus;

struct DummyBus {
  Bus;
  int value;
};

void *DummyBusInit(DummyBus *);
void DummyBusFini(DummyBus *);
int DummyBusLock(DummyBus *me,unsigned num,int flags);
int DummyBusUnlock(DummyBus *me,unsigned num,int flags);
int DummyBusPreempt(DummyBus *me);
unsigned char DummyBusPeek8(DummyBus *,int adrs);
void DummyBusPoke8(DummyBus *,int adrs,unsigned char val);
unsigned short DummyBusPeek16(DummyBus *,int adrs);
void DummyBusPoke16(DummyBus *,int adrs,unsigned short val);
unsigned DummyBusPeek32(DummyBus *,int adrs);
void DummyBusPoke32(DummyBus *,int adrs,unsigned val);
int DummyBusBitGet8(DummyBus *bus,int adrs,int bit);
void DummyBusBitAssign8(DummyBus *bus,int adrs,int bit,int val);
void DummyBusBitSet8(DummyBus *bus,int adrs,int bit);
void DummyBusBitClear8(DummyBus *bus,int adrs,int bit);
int DummyBusBitGet16(DummyBus *bus,int adrs,int bit);
void DummyBusBitAssign16(DummyBus *bus,int adrs,int bit,int val);
void DummyBusBitSet16(DummyBus *bus,int adrs,int bit);
void DummyBusBitClear16(DummyBus *bus,int adrs,int bit);
int DummyBusBitGet32(DummyBus *bus,int adrs,int bit);
void DummyBusBitAssign32(DummyBus *bus,int adrs,int bit,int val);
void DummyBusBitSet32(DummyBus *bus,int adrs,int bit);
void DummyBusBitClear32(DummyBus *bus,int adrs,int bit);
void DummyBusPeekStream(DummyBus *bus,int adr,int dir,char* buf);
void DummyBusPokeStream(DummyBus *bus,int adr,int dir,const char* buf);
void DummyBusRefresh(DummyBus *);
void DummyBusCommit(DummyBus *,int forceall);
int DummyBusBitToggle8(DummyBus *bus,int adrs,int bit);
int DummyBusBitToggle16(DummyBus *bus,int adrs,int bit);
int DummyBusBitToggle32(DummyBus *bus,int adrs,int bit);
unsigned char DummyBusAssign8X(DummyBus *,int adrs,int bit1,int bit0,int val);
unsigned short DummyBusAssign16X(DummyBus *,int adrs,int bit1,int bit0,int val);
unsigned DummyBusAssign32X(DummyBus *,int adrs,int bit1,int bit0,int val);
unsigned char DummyBusBitsGet8(DummyBus *,int adrs,int bit1,int bit0);
unsigned short DummyBusBitsGet16(DummyBus *,int adrs,int bit1,int bit0);
unsigned DummyBusBitsGet32(DummyBus *,int adrs,int bit1,int bit0);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
