#ifndef MMapBus_c
#define MMapBus_c
//#include <sched.h>
//#include "Obj.h"
#include "MMapBus.h"
#include "peekpoke.h"
#include "Bit.h"
#include "Array.h"

#define LOCK_TYPE_SHARED
#define LOCK_CLASS MMapBus
#include "TSLock.h"

void *MMapBusInit2(void *bus0,void *mem,int Pages) {
  MMapBus *bus = bus0;
  if (bus->InitStatus > 0) return bus;
  MMapBusLockInit(bus,1);

  bus->Init = (void *)MMapBusInit;
  bus->Fini = (void *)MMapBusFini;
  bus->Lock = (void *)MMapBusLock;
  bus->Unlock = (void *)MMapBusUnlock;
  bus->Preempt = (void *)MMapBusPreempt;
  bus->Peek8 = (void *)MMapBusPeek8;
  bus->Poke8 = (void *)MMapBusPoke8;
  bus->Peek16 = (void *)MMapBusPeek16;
  bus->Poke16 = (void *)MMapBusPoke16;
  bus->Peek32 = (void *)MMapBusPeek32;
  bus->Poke32 = (void *)MMapBusPoke32;
  bus->BitGet8 = (void *)MMapBusBitGet8;
  bus->BitAssign8 = (void *)MMapBusBitAssign8;
  bus->BitSet8 = (void *)MMapBusBitSet8;
  bus->BitClear8 = (void *)MMapBusBitClear8;
  bus->BitGet16 = (void *)MMapBusBitGet16;
  bus->BitAssign16 = (void *)MMapBusBitAssign16;
  bus->BitSet16 = (void *)MMapBusBitSet16;
  bus->BitClear16 = (void *)MMapBusBitClear16;
  bus->BitGet32 = (void *)MMapBusBitGet32;
  bus->BitAssign32 = (void *)MMapBusBitAssign32;
  bus->BitSet32 = (void *)MMapBusBitSet32;
  bus->BitClear32 = (void *)MMapBusBitClear32;
  bus->PeekStream = (void *)MMapBusPeekStream;
  bus->PokeStream = (void *)MMapBusPokeStream;
  bus->Refresh = (void *)MMapBusRefresh;
  bus->Commit = (void *)MMapBusCommit;
  bus->BitToggle8 = (void *)MMapBusBitToggle8;
  bus->BitToggle16 = (void *)MMapBusBitToggle16;
  bus->BitToggle32 = (void *)MMapBusBitToggle32;
  bus->Assign8X = (void *)MMapBusAssign8X;
  bus->Assign16X = (void *)MMapBusAssign16X;
  bus->Assign32X = (void *)MMapBusAssign32X;
  bus->BitsGet8 = (void *)MMapBusBitsGet8;
  bus->BitsGet16 = (void *)MMapBusBitsGet16;
  bus->BitsGet32 = (void *)MMapBusBitsGet32;

  bus->Mem = bus->Mem16 = mem;
  bus->InitStatus = 1;
  return bus;
}

void *MMapBusInit(MMapBus *bus,int MemBase,int Pages) {
  if (bus->InitStatus > 0) return bus;

  bus->Init = (void *)MMapBusInit;
  bus->Fini = (void *)MMapBusFini;
  bus->Lock = (void *)MMapBusLock;
  bus->Unlock = (void *)MMapBusUnlock;
  bus->Preempt = (void *)MMapBusPreempt;
  bus->Peek8 = (void *)MMapBusPeek8;
  bus->Poke8 = (void *)MMapBusPoke8;
  bus->Peek16 = (void *)MMapBusPeek16;
  bus->Poke16 = (void *)MMapBusPoke16;
  bus->Peek32 = (void *)MMapBusPeek32;
  bus->Poke32 = (void *)MMapBusPoke32;
  bus->BitGet8 = (void *)MMapBusBitGet8;
  bus->BitAssign8 = (void *)MMapBusBitAssign8;
  bus->BitSet8 = (void *)MMapBusBitSet8;
  bus->BitClear8 = (void *)MMapBusBitClear8;
  bus->BitGet16 = (void *)MMapBusBitGet16;
  bus->BitAssign16 = (void *)MMapBusBitAssign16;
  bus->BitSet16 = (void *)MMapBusBitSet16;
  bus->BitClear16 = (void *)MMapBusBitClear16;
  bus->BitGet32 = (void *)MMapBusBitGet32;
  bus->BitAssign32 = (void *)MMapBusBitAssign32;
  bus->BitSet32 = (void *)MMapBusBitSet32;
  bus->BitClear32 = (void *)MMapBusBitClear32;
  bus->PeekStream = (void *)MMapBusPeekStream;
  bus->PokeStream = (void *)MMapBusPokeStream;
  bus->Refresh = (void *)MMapBusRefresh;
  bus->Commit = (void *)MMapBusCommit;
  bus->BitToggle8 = (void *)MMapBusBitToggle8;
  bus->BitToggle16 = (void *)MMapBusBitToggle16;
  bus->BitToggle32 = (void *)MMapBusBitToggle32;
  bus->Assign8X = (void *)MMapBusAssign8X;
  bus->Assign16X = (void *)MMapBusAssign16X;
  bus->Assign32X = (void *)MMapBusAssign32X;
  bus->BitsGet8 = (void *)MMapBusBitsGet8;
  bus->BitsGet16 = (void *)MMapBusBitsGet16;
  bus->BitsGet32 = (void *)MMapBusBitsGet32;
  
  MMapBusLockInit(bus,1);
  if (Pages <= 0) {
    Pages = 1;
  }
  if (bus->Mem == 0) { // make multiple calls to Init safe
    bus->Mem = bus->Mem16 = MemMap(MemBase,Pages);
  }
  bus->InitStatus = (bus->Mem == 0) ? MapBusErrorMapping : 1;
  return bus;
}

void *MMapBusInit3(MMapBus *bus0,int MemBase8,int MemBase16,int Pages) {
  bus0 = MMapBusInit(bus0,MemBase8,Pages);
  if (Pages <= 0) Pages = 1;
  if (bus0->Mem16 == 0) { // make multiple calls to Init safe
    bus0->Mem16 = MemMap(MemBase16,Pages);
  }
  return bus0;
}


void MMapBusFini(MMapBus *bus) {
  if (bus->Mem) {
    MemUnmap(bus->Mem);
    bus->Mem = 0;
  }
  if (bus->Mem16) {
    MemUnmap(bus->Mem16);
    bus->Mem16 = 0;
  }
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

void MMapBusRefresh(MMapBus *bus) {
  // nothing to do
}

void MMapBusCommit(MMapBus *bus,int forceall) {
  // nothing to do
}

//-----------------------------------------------------------------------------
#define PTR(x) ((char *)(MEM))
//#define DEBUG
//#define DEBUG_ADRS bus
#ifdef DEBUG
#include <stdio.h>
#endif

__attribute__((always_inline)) 
static inline unsigned char _MMapBusPeek8(MMapBus *bus,int adrs) {
  unsigned char ret = bus->Mem[adrs];
#ifdef DEBUG
  if (bus == DEBUG_ADRS)
  fprintf(stderr,"%p:Peek8 0x%X = %02X\n",bus,adrs,ret);
#endif
  return ret;
}

__attribute__((always_inline)) 
static inline void _MMapBusPoke8(MMapBus *bus,int adrs,unsigned char val) {
#ifdef DEBUG
  if (bus == DEBUG_ADRS)
  fprintf(stderr,"%p:Poke8 0x%X,%04X\n",bus,adrs,val);
#endif
  bus->Mem[adrs] = val;
}

__attribute__((always_inline)) 
static inline unsigned short _MMapBusPeek16(MMapBus *bus,int adrs) {
  unsigned short ret = ((volatile unsigned short *)(bus->Mem16+adrs))[0];
#ifdef DEBUG
  if (bus == DEBUG_ADRS)
  fprintf(stderr,"%p:Peek16 0x%X = %04X\n",bus,adrs,ret);
#endif
  return ret;
}

#if 0
extern MMapBus ts4700DIOBus;
MMapBus *DBUS = &ts4700DIOBus;
#endif
__attribute__((always_inline)) 
static inline void _MMapBusPoke16(MMapBus *bus,int adrs,unsigned short val) {
#if 0
  if (bus == DBUS && adrs == 2 && !(val & (1<<11))) {
    fprintf(stderr,"Poke16 0x%X,%X\n",adrs,val);
    assert(0);
  }
#endif
#ifdef DEBUG
  if (bus == DEBUG_ADRS)
  fprintf(stderr,"%p:Poke16 0x%X,%X\n",bus,adrs,val);
#endif
  ((volatile unsigned short *)(bus->Mem16+adrs))[0] = val;
}

__attribute__((always_inline)) 
static inline unsigned _MMapBusPeek32(MMapBus *bus,int adrs) {
#ifdef DEBUG
  if (bus == DEBUG_ADRS)
  fprintf(stderr,"%p:Peek32 %d\n",bus,adrs);
#endif
  return ((volatile unsigned *)(bus->Mem+adrs))[0];
}

__attribute__((always_inline)) 
static inline void _MMapBusPoke32(MMapBus *bus,int adrs,unsigned val)  {
#ifdef DEBUG
  if (bus == DEBUG_ADRS)
  fprintf(stderr,"%p:Poke32 %d,%X\n",bus,adrs,val);
#endif
  ((volatile unsigned *)(bus->Mem+adrs))[0] = val;
}
#undef DEBUG
//-----------------------------------------------------------------------------
DefinitionFunctionsBit(MMapBus,unsigned char,8)
DefinitionFunctionsBit(MMapBus,unsigned short,16)
DefinitionFunctionsBit(MMapBus,unsigned,32)

void MMapBusPeekStream(MMapBus *bus,int adr,int dir,char* buf) {
  int i,len = ArrayLength(buf);
  //fprintf(stderr,"PeekStream(%d,%d by %d)\n",adr,len,dir);
  for (i=0;i<len;i++) {
    buf[i] = _MMapBusPeek8(bus,adr);
    adr += dir;
  }
}

void MMapBusPokeStream(MMapBus *bus,int adr,int dir,const char* buf) {
  //((volatile unsigned char *)(PTR(MEM)+adr))[0] = val;
  int i,len = ArrayLength(buf);
  //fprintf(stderr,"PokeStream(%d,%d by %d)\n",adr,len,dir);
  for (i=0;i<len;i++) {
    _MMapBusPoke8(bus,adr,buf[i]);
    adr += dir;
  }
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
