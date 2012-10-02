#include <stdlib.h>
#include "Cavium2132SBusWindowBus.h"
#include "Bit.h"
#include "Array.h"

static BusAPI Cavium2132SBusWindowBusAPI = {
  .Init = (void *)Cavium2132SBusWindowBusInit,
  .Fini = (void *)Cavium2132SBusWindowBusFini,
  .Lock = (void *)Cavium2132SBusWindowBusLock,
  .Unlock = (void *)Cavium2132SBusWindowBusUnlock,
  .Preempt = (void *)Cavium2132SBusWindowBusPreempt,
  .Peek8 = (void *)Cavium2132SBusWindowBusPeek8,
  .Poke8 = (void *)Cavium2132SBusWindowBusPoke8,
  .Peek16 = (void *)Cavium2132SBusWindowBusPeek16,
  .Poke16 = (void *)Cavium2132SBusWindowBusPoke16,
  .Peek32 = (void *)Cavium2132SBusWindowBusPeek32,
  .Poke32 = (void *)Cavium2132SBusWindowBusPoke32,
  .BitGet8 = (void *)Cavium2132SBusWindowBusBitGet8,
  .BitAssign8 = (void *)Cavium2132SBusWindowBusBitAssign8,
  .BitSet8 = (void *)Cavium2132SBusWindowBusBitSet8,
  .BitClear8 = (void *)Cavium2132SBusWindowBusBitClear8,
  .BitGet16 = (void *)Cavium2132SBusWindowBusBitGet16,
  .BitAssign16 = (void *)Cavium2132SBusWindowBusBitAssign16,
  .BitSet16 = (void *)Cavium2132SBusWindowBusBitSet16,
  .BitClear16 = (void *)Cavium2132SBusWindowBusBitClear16,
  .BitGet32 = (void *)Cavium2132SBusWindowBusBitGet32,
  .BitAssign32 = (void *)Cavium2132SBusWindowBusBitAssign32,
  .BitSet32 = (void *)Cavium2132SBusWindowBusBitSet32,
  .BitClear32 = (void *)Cavium2132SBusWindowBusBitClear32,
  .PeekStream = (void *)Cavium2132SBusWindowBusPeekStream,
  .PokeStream = (void *)Cavium2132SBusWindowBusPokeStream,
  .Refresh = (void *)Cavium2132SBusWindowBusRefresh,
  .Commit = (void *)Cavium2132SBusWindowBusCommit,
  .BitToggle8 = (void *)Cavium2132SBusWindowBusBitToggle8,
  .BitToggle16 = (void *)Cavium2132SBusWindowBusBitToggle16,
  .BitToggle32 = (void *)Cavium2132SBusWindowBusBitToggle32,
  .Assign8X = (void *)Cavium2132SBusWindowBusAssign8X,
  .Assign16X = (void *)Cavium2132SBusWindowBusAssign16X,
  .Assign32X = (void *)Cavium2132SBusWindowBusAssign32X,
  .BitsGet8 = (void *)Cavium2132SBusWindowBusBitsGet8,
  .BitsGet16 = (void *)Cavium2132SBusWindowBusBitsGet16,
  .BitsGet32 = (void *)Cavium2132SBusWindowBusBitsGet32
};

void *Cavium2132SBusWindowBusInit(Cavium2132SBusWindowBus *bus,void *sbus0) {
  if (bus->InitStatus > 0) return bus;
  bus->sbus = sbus0;
  if (bus->sbus->InitStatus < 0) {
    bus->Fini(bus);
    bus->InitStatus = -1;
    return bus;
  }

  bus->Init = (void *)Cavium2132SBusWindowBusInit;
  bus->Fini = (void *)Cavium2132SBusWindowBusFini;
  bus->Lock = (void *)Cavium2132SBusWindowBusLock;
  bus->Unlock = (void *)Cavium2132SBusWindowBusUnlock;
  bus->Preempt = (void *)Cavium2132SBusWindowBusPreempt;
  bus->Peek8 = (void *)Cavium2132SBusWindowBusPeek8;
  bus->Poke8 = (void *)Cavium2132SBusWindowBusPoke8;
  bus->Peek16 = (void *)Cavium2132SBusWindowBusPeek16;
  bus->Poke16 = (void *)Cavium2132SBusWindowBusPoke16;
  bus->Peek32 = (void *)Cavium2132SBusWindowBusPeek32;
  bus->Poke32 = (void *)Cavium2132SBusWindowBusPoke32;
  bus->BitGet8 = (void *)Cavium2132SBusWindowBusBitGet8;
  bus->BitAssign8 = (void *)Cavium2132SBusWindowBusBitAssign8;
  bus->BitSet8 = (void *)Cavium2132SBusWindowBusBitSet8;
  bus->BitClear8 = (void *)Cavium2132SBusWindowBusBitClear8;
  bus->BitGet16 = (void *)Cavium2132SBusWindowBusBitGet16;
  bus->BitAssign16 = (void *)Cavium2132SBusWindowBusBitAssign16;
  bus->BitSet16 = (void *)Cavium2132SBusWindowBusBitSet16;
  bus->BitClear16 = (void *)Cavium2132SBusWindowBusBitClear16;
  bus->BitGet32 = (void *)Cavium2132SBusWindowBusBitGet32;
  bus->BitAssign32 = (void *)Cavium2132SBusWindowBusBitAssign32;
  bus->BitSet32 = (void *)Cavium2132SBusWindowBusBitSet32;
  bus->BitClear32 = (void *)Cavium2132SBusWindowBusBitClear32;
  bus->PeekStream = (void *)Cavium2132SBusWindowBusPeekStream;
  bus->PokeStream = (void *)Cavium2132SBusWindowBusPokeStream;
  bus->Refresh = (void *)Cavium2132SBusWindowBusRefresh;
  bus->Commit = (void *)Cavium2132SBusWindowBusCommit;
  bus->BitToggle8 = (void *)Cavium2132SBusWindowBusBitToggle8;
  bus->BitToggle16 = (void *)Cavium2132SBusWindowBusBitToggle16;
  bus->BitToggle32 = (void *)Cavium2132SBusWindowBusBitToggle32;
  bus->Assign8X = (void *)Cavium2132SBusWindowBusAssign8X;
  bus->Assign16X = (void *)Cavium2132SBusWindowBusAssign16X;
  bus->Assign32X = (void *)Cavium2132SBusWindowBusAssign32X;
  bus->BitsGet8 = (void *)Cavium2132SBusWindowBusBitsGet8;
  bus->BitsGet16 = (void *)Cavium2132SBusWindowBusBitsGet16;
  bus->BitsGet32 = (void *)Cavium2132SBusWindowBusBitsGet32;

  bus->AdrsLast = -1;
  bus->InitStatus = 1;
  return bus;
}

void Cavium2132SBusWindowBusFini(Cavium2132SBusWindowBus *bus) {
  bus->sbus->Fini(bus->sbus);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

static unsigned char _Cavium2132SBusWindowBusPeek8(Cavium2132SBusWindowBus *bus,int adr){
  unsigned char ret;

  if (adr != bus->AdrsLast) {
    bus->sbus->Poke16(bus->sbus,bus->MemBase,adr);
  }
  bus->AdrsLast = adr + 1;
  ret = bus->sbus->Peek16(bus->sbus,bus->MemBase+2) & 0xFF;
  return ret;
}

int Cavium2132SBusWindowBusLock(Cavium2132SBusWindowBus *bus,
				unsigned num,int flags) {
  return bus->sbus->Lock(bus->sbus,num,flags);
}

int Cavium2132SBusWindowBusUnlock(Cavium2132SBusWindowBus *bus,
				unsigned num,int flags) {
  return bus->sbus->Unlock(bus->sbus,num,flags);
}

int Cavium2132SBusWindowBusPreempt(Cavium2132SBusWindowBus *bus) {
  return bus->sbus->Preempt(bus->sbus);
}

static void _Cavium2132SBusWindowBusPoke8(Cavium2132SBusWindowBus *bus,int adr, unsigned char dat){
  dat &= 0xFF;
  bus->sbus->Poke16(bus->sbus,bus->MemBase+6,adr<<8 | dat);
  bus->AdrsLast = adr + 1;
}

static unsigned short _Cavium2132SBusWindowBusPeek16(Cavium2132SBusWindowBus *bus,int adr){
  return 0; // unsupported
}

static void _Cavium2132SBusWindowBusPoke16(Cavium2132SBusWindowBus *bus,int adr, unsigned short dat){
  // unsupported
}

static unsigned _Cavium2132SBusWindowBusPeek32(Cavium2132SBusWindowBus *bus,int adr){
  // unsupported
}

static void _Cavium2132SBusWindowBusPoke32(Cavium2132SBusWindowBus *bus,int adr, unsigned dat){
  // unsupported
}

void Cavium2132SBusWindowBusPeekStream(Cavium2132SBusWindowBus *bus,int adr,int dir,char* buf){
  int len = ArrayLength(buf);
  if (len <= 0) return;
  if (adr != bus->AdrsLast) {
    bus->sbus->Poke16(bus->sbus,bus->MemBase,adr);
  }
  bus->AdrsLast = adr + len;
  while (len >= 2) {
    unsigned int s = bus->sbus->Peek16(bus->sbus,bus->MemBase+4);
    *buf++ = s & 0xff;
    *buf++ = s >> 8;
    len -= 2;
  }
  if (len) *buf = bus->sbus->Peek16(bus->sbus,bus->MemBase+2) & 0xFF;
}

void Cavium2132SBusWindowBusPokeStream(Cavium2132SBusWindowBus *bus,int adr,int dir,const char* buf){
  int len = ArrayLength(buf);
  int na = adr + len + 1;
  if (len <= 0) return;

  if (adr != bus->AdrsLast) {
    // The next two lines of code are equivalent to:
    //     bus->Poke8(bus->sbus,adr, *buf++);
    // except that we don't try to lock the SBus, because we already
    // have the lock!
    bus->sbus->Poke16(bus->sbus,bus->MemBase+6,adr<<8 | *buf++);
    bus->AdrsLast = adr + 1;
    len--;
  } 
	
  bus->AdrsLast = na;

  while (len >= 2) {
    unsigned int s;
    s = *buf++;
    s |= *buf++ << 8;
    bus->sbus->Poke16(bus->sbus,bus->MemBase+4, s);
    len -= 2;
  }

  if (len) bus->sbus->Poke16(bus->sbus,bus->MemBase+2, *buf);
}

DefinitionFunctionsBit(Cavium2132SBusWindowBus,unsigned char,8)
DefinitionFunctionsBit(Cavium2132SBusWindowBus,unsigned short,16)
DefinitionFunctionsBit(Cavium2132SBusWindowBus,unsigned,32)

void Cavium2132SBusWindowBusRefresh(Cavium2132SBusWindowBus *bus) {
  bus->sbus->Refresh(bus->sbus);
}

void Cavium2132SBusWindowBusCommit(Cavium2132SBusWindowBus *bus,int forceall) {
  bus->sbus->Commit(bus->sbus,forceall);
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
