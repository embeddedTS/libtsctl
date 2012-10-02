#ifndef __Cavium2132SBusWindowBus_h
#define __Cavium2132SBusWindowBus_h
#include "Bus.h"
typedef struct Cavium2132SBusWindowBus Cavium2132SBusWindowBus ;
struct Cavium2132SBusWindowBus {
  Bus;
  Bus *sbus;
  int AdrsLast, MemBase;
};

void *Cavium2132SBusWindowBusInit(Cavium2132SBusWindowBus *,void *sbus);
void Cavium2132SBusWindowBusFini(Cavium2132SBusWindowBus *);
int Cavium2132SBusWindowBusLock(Cavium2132SBusWindowBus *bus,
				unsigned num,int flags);
int Cavium2132SBusWindowBusUnlock(Cavium2132SBusWindowBus *bus,
				  unsigned num,int flags);
int Cavium2132SBusWindowBusPreempt(Cavium2132SBusWindowBus *bus);

unsigned char Cavium2132SBusWindowBusPeek8(Cavium2132SBusWindowBus *,int adrs);
void Cavium2132SBusWindowBusPoke8(Cavium2132SBusWindowBus *,int adrs,unsigned char val);
unsigned short Cavium2132SBusWindowBusPeek16(Cavium2132SBusWindowBus *,int adrs);
void Cavium2132SBusWindowBusPoke16(Cavium2132SBusWindowBus *,int adrs,unsigned short val);
unsigned Cavium2132SBusWindowBusPeek32(Cavium2132SBusWindowBus *,int adrs);
void Cavium2132SBusWindowBusPoke32(Cavium2132SBusWindowBus *,int adrs,unsigned val);
int Cavium2132SBusWindowBusBitGet8(Cavium2132SBusWindowBus *bus,int adrs,int bit);
void Cavium2132SBusWindowBusBitAssign8(Cavium2132SBusWindowBus *bus,int adrs,int bit,int val);
void Cavium2132SBusWindowBusBitSet8(Cavium2132SBusWindowBus *bus,int adrs,int bit);
void Cavium2132SBusWindowBusBitClear8(Cavium2132SBusWindowBus *bus,int adrs,int bit);
int Cavium2132SBusWindowBusBitGet16(Cavium2132SBusWindowBus *bus,int adrs,int bit);
void Cavium2132SBusWindowBusBitAssign16(Cavium2132SBusWindowBus *bus,int adrs,int bit,int val);
void Cavium2132SBusWindowBusBitSet16(Cavium2132SBusWindowBus *bus,int adrs,int bit);
void Cavium2132SBusWindowBusBitClear16(Cavium2132SBusWindowBus *bus,int adrs,int bit);
int Cavium2132SBusWindowBusBitGet32(Cavium2132SBusWindowBus *bus,int adrs,int bit);
void Cavium2132SBusWindowBusBitAssign32(Cavium2132SBusWindowBus *bus,int adrs,int bit,int val);
void Cavium2132SBusWindowBusBitSet32(Cavium2132SBusWindowBus *bus,int adrs,int bit);
void Cavium2132SBusWindowBusBitClear32(Cavium2132SBusWindowBus *bus,int adrs,int bit);
void Cavium2132SBusWindowBusPeekStream(Cavium2132SBusWindowBus *bus,int adr,int dir,char* buf);
void Cavium2132SBusWindowBusPokeStream(Cavium2132SBusWindowBus *bus,int adr,int dir,const char* buf);
void Cavium2132SBusWindowBusRefresh(Cavium2132SBusWindowBus *);
void Cavium2132SBusWindowBusCommit(Cavium2132SBusWindowBus *,int forceall);
int Cavium2132SBusWindowBusBitToggle8(Cavium2132SBusWindowBus *bus,int adrs,int bit);
int Cavium2132SBusWindowBusBitToggle16(Cavium2132SBusWindowBus *bus,int adrs,int bit);
int Cavium2132SBusWindowBusBitToggle32(Cavium2132SBusWindowBus *bus,int adrs,int bit);
unsigned char Cavium2132SBusWindowBusAssign8X(Cavium2132SBusWindowBus *,int adrs,int bit1,int bit0,int val);
unsigned short Cavium2132SBusWindowBusAssign16X(Cavium2132SBusWindowBus *,int adrs,int bit1,int bit0,int val);
unsigned Cavium2132SBusWindowBusAssign32X(Cavium2132SBusWindowBus *,int adrs,int bit1,int bit0,int val);
unsigned char Cavium2132SBusWindowBusBitsGet8(Cavium2132SBusWindowBus *,int adrs,int bit1,int bit0);
unsigned short Cavium2132SBusWindowBusBitsGet16(Cavium2132SBusWindowBus *,int adrs,int bit1,int bit0);
unsigned Cavium2132SBusWindowBusBitsGet32(Cavium2132SBusWindowBus *,int adrs,int bit1,int bit0);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
