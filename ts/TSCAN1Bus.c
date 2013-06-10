#ifndef __TSCAN1Bus_c
#define __TSCAN1Bus_c
#include <assert.h>
#include "TSCAN1Bus.h"
#include "Bit.h"
#include "Thread.h"

__attribute__((always_inline)) 
static inline void TSCAN1BusLockCallback(TSCAN1Bus *bus,int num) {
  
}


#define LOCK_TYPE_SHARED
#define LOCK_CLASS TSCAN1Bus
#define LOCK_CALLBACK TSCAN1BusLockCallback
#include "TSLock.h"

void *TSCAN1BusInit(TSCAN1Bus *bus,void *sub0,int base) {
  Bus *sub = sub0;
  if (bus->InitStatus > 0) return bus;

  bus->Init = (void *)TSCAN1BusInit;
  bus->Fini = (void *)TSCAN1BusFini;
  bus->Lock = (void *)TSCAN1BusLock;
  bus->Unlock = (void *)TSCAN1BusUnlock;
  bus->Preempt = (void *)TSCAN1BusPreempt;
  bus->Peek8 = (void *)TSCAN1BusPeek8;
  bus->Poke8 = (void *)TSCAN1BusPoke8;
  bus->Peek16 = (void *)TSCAN1BusPeek16;
  bus->Poke16 = (void *)TSCAN1BusPoke16;
  bus->Peek32 = (void *)TSCAN1BusPeek32;
  bus->Poke32 = (void *)TSCAN1BusPoke32;
  bus->BitGet8 = (void *)TSCAN1BusBitGet8;
  bus->BitAssign8 = (void *)TSCAN1BusBitAssign8;
  bus->BitSet8 = (void *)TSCAN1BusBitSet8;
  bus->BitClear8 = (void *)TSCAN1BusBitClear8;
  bus->BitGet16 = (void *)TSCAN1BusBitGet16;
  bus->BitAssign16 = (void *)TSCAN1BusBitAssign16;
  bus->BitSet16 = (void *)TSCAN1BusBitSet16;
  bus->BitClear16 = (void *)TSCAN1BusBitClear16;
  bus->BitGet32 = (void *)TSCAN1BusBitGet32;
  bus->BitAssign32 = (void *)TSCAN1BusBitAssign32;
  bus->BitSet32 = (void *)TSCAN1BusBitSet32;
  bus->BitClear32 = (void *)TSCAN1BusBitClear32;
  bus->PeekStream = (void *)TSCAN1BusPeekStream;
  bus->PokeStream = (void *)TSCAN1BusPokeStream;
  bus->Refresh = (void *)TSCAN1BusRefresh;
  bus->Commit = (void *)TSCAN1BusCommit;
  bus->BitToggle8 = (void *)TSCAN1BusBitToggle8;
  bus->BitToggle16 = (void *)TSCAN1BusBitToggle16;
  bus->BitToggle32 = (void *)TSCAN1BusBitToggle32;
  bus->Assign8X = (void *)TSCAN1BusAssign8X;
  bus->Assign16X = (void *)TSCAN1BusAssign16X;
  bus->Assign32X = (void *)TSCAN1BusAssign32X;
  bus->BitsGet8 = (void *)TSCAN1BusBitsGet8;
  bus->BitsGet16 = (void *)TSCAN1BusBitsGet16;
  bus->BitsGet32 = (void *)TSCAN1BusBitsGet32;

  bus->base0 = base;
  sub->Lock(sub,0,0);
  if (sub->Peek8(sub,base) != 0xF6 || sub->Peek8(sub,base+1) != 0xB9) {
    sub->Unlock(sub,0,0);
    return 0;
  }
  bus->base1 = sub->BitsGet8(sub,base+5,2,0);
  sub->Unlock(sub,0,0);
  switch (bus->base1) {
  case 0: bus->base1 = 0x100; break;
  case 1: bus->base1 = 0x120; break;
  case 2: bus->base1 = 0x180; break;
  case 3: bus->base1 = 0x1A0; break;
  case 4: bus->base1 = 0x200; break;
  case 5: bus->base1 = 0x240; break;
  case 6: bus->base1 = 0x280; break;
  case 7: bus->base1 = 0x320; break;
  }
  bus->bank = -1;

  TSCAN1BusLockInit(bus,1);

  bus->sub = sub;
  assert(bus->sub);
  if (bus->sub->InitStatus <= 0) {
    bus->Fini(bus);
    bus->InitStatus = -1;
    return bus;
  }
  bus->InitStatus = 1;
  return bus;
}

void TSCAN1BusFini(TSCAN1Bus *bus) {
  assert(bus->sub);
  bus->sub->Fini(bus->sub);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

void TSCAN1BusRefresh(TSCAN1Bus *bus) {
  // nothing to do
}

void TSCAN1BusCommit(TSCAN1Bus *bus,int forceall) {
  // nothing to do
}

void TSCAN1BusPeekStream(TSCAN1Bus *bus,int adr,int dir,char* buf) {
  // TO DO: support this function
}

void TSCAN1BusPokeStream(TSCAN1Bus *bus,int adr,int dir,const char* buf) {
  // TO DO: support this function
}


//-----------------------------------------------------------------------------
__attribute__((always_inline)) 
static inline unsigned char _TSCAN1BusPeek8(TSCAN1Bus *bus,int adrs) {
  int newbank = (adrs / 32) & 3;
  if (newbank != bus->bank) {
    bus->bank = newbank;
    bus->sub->Poke8(bus->sub,bus->base0+4,bus->bank);
  }
  return bus->sub->Peek8(bus->sub,bus->base1 + adrs % 32);
}

__attribute__((always_inline)) 
static inline void _TSCAN1BusPoke8(TSCAN1Bus *bus,int adrs,unsigned char val) {
  int newbank = (adrs / 32) & 3;
  if (newbank != bus->bank) {
    bus->bank = newbank;
    bus->sub->Poke8(bus->sub,bus->base0+4,bus->bank);
  }
  return bus->sub->Poke8(bus->sub,bus->base1 + adrs % 32,val);
}

// note: adrs & 1 != 0 not supported
__attribute__((always_inline)) 
static inline unsigned short _TSCAN1BusPeek16(TSCAN1Bus *bus,int adrs) {
  return 0;
}

__attribute__((always_inline)) 
static inline void _TSCAN1BusPoke16(TSCAN1Bus *bus,int adrs,unsigned short val) {
}

__attribute__((always_inline)) 
static inline unsigned _TSCAN1BusPeek32(TSCAN1Bus *bus,int adrs) {
  return 0;
}

__attribute__((always_inline)) 
static inline void _TSCAN1BusPoke32(TSCAN1Bus *bus,int adrs,unsigned val) {
}
//-----------------------------------------------------------------------------
DefinitionFunctionsBit(TSCAN1Bus,unsigned char,8)
DefinitionFunctionsBit(TSCAN1Bus,unsigned short,16)
DefinitionFunctionsBit(TSCAN1Bus,unsigned,32)


#endif
