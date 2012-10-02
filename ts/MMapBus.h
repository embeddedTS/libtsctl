#ifndef __MMapBus_h
#define __MMapBus_h
#include "Bus.h"

typedef struct MMapBus MMapBus;

struct MMapBus {
  Bus;
  volatile char *Mem;
};

void *MMapBusInit(MMapBus *,int MMapBase,int Pages);
void *MMapBusInit2(MMapBus *,void *mem,int Pages);
void MMapBusFini(MMapBus *);
unsigned char MMapBusPeek8(MMapBus *,int adrs);
void MMapBusPoke8(MMapBus *,int adrs,unsigned char val);
unsigned short MMapBusPeek16(MMapBus *,int adrs);
void MMapBusPoke16(MMapBus *,int adrs,unsigned short val);
unsigned MMapBusPeek32(MMapBus *,int adrs);
void MMapBusPoke32(MMapBus *,int adrs,unsigned val);
int MMapBusBitGet8(MMapBus *bus,int adrs,int bit);
void MMapBusBitAssign8(MMapBus *bus,int adrs,int bit,int val);
void MMapBusBitSet8(MMapBus *bus,int adrs,int bit);
void MMapBusBitClear8(MMapBus *bus,int adrs,int bit);
int MMapBusBitGet16(MMapBus *bus,int adrs,int bit);
void MMapBusBitAssign16(MMapBus *bus,int adrs,int bit,int val);
void MMapBusBitSet16(MMapBus *bus,int adrs,int bit);
void MMapBusBitClear16(MMapBus *bus,int adrs,int bit);
int MMapBusBitGet32(MMapBus *bus,int adrs,int bit);
void MMapBusBitAssign32(MMapBus *bus,int adrs,int bit,int val);
void MMapBusBitSet32(MMapBus *bus,int adrs,int bit);
void MMapBusBitClear32(MMapBus *bus,int adrs,int bit);
void MMapBusPeekStream(MMapBus *bus,int adr,int dir,char* buf);
void MMapBusPokeStream(MMapBus *bus,int adr,int dir,const char* buf);
void MMapBusRefresh(MMapBus *);
void MMapBusCommit(MMapBus *,int forceall);
int MMapBusBitToggle8(MMapBus *bus,int adrs,int bit);
int MMapBusBitToggle16(MMapBus *bus,int adrs,int bit);
int MMapBusBitToggle32(MMapBus *bus,int adrs,int bit);
unsigned char MMapBusAssign8X(MMapBus *,int adrs,int bit1,int bit0,int val);
unsigned short MMapBusAssign16X(MMapBus *,int adrs,int bit1,int bit0,int val);
unsigned MMapBusAssign32X(MMapBus *,int adrs,int bit1,int bit0,int val);
unsigned char MMapBusBitsGet8(MMapBus *,int adrs,int bit1,int bit0);
unsigned short MMapBusBitsGet16(MMapBus *,int adrs,int bit1,int bit0);
unsigned MMapBusBitsGet32(MMapBus *,int adrs,int bit1,int bit0);

enum {
  MapBusErrorMapping=-100
};

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
