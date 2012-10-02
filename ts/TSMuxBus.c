#ifndef TSMuxBus_c
#define TSMuxBus_c
#include <assert.h>
#include "TSMuxBus.h"
#include "Bit.h"
#include "Thread.h"

static inline void TSMuxBusLockCallback(TSMuxBus *bus,int num) {
  assert(bus->configbus);
  bus->configbus->Lock(bus->configbus,num,0);
  bus->configbus->Poke16(bus->configbus,bus->cadrs,0x321); // 0x181, 0x321 or ff7f
  bus->configbus->Unlock(bus->configbus,num,0);
}

#define LOCK_TYPE_SHARED
#define LOCK_CLASS TSMuxBus
#define LOCK_CALLBACK TSMuxBusLockCallback
#include "TSLock.h"

static BusAPI TSMuxBusAPI = {
  .Init = (void *)TSMuxBusInit,
  .Fini = (void *)TSMuxBusFini,
  .Lock = (void *)TSMuxBusLock,
  .Unlock = (void *)TSMuxBusUnlock,
  .Preempt = (void *)TSMuxBusPreempt,
  .Peek8 = (void *)TSMuxBusPeek8,
  .Poke8 = (void *)TSMuxBusPoke8,
  .Peek16 = (void *)TSMuxBusPeek16,
  .Poke16 = (void *)TSMuxBusPoke16,
  .Peek32 = (void *)TSMuxBusPeek32,
  .Poke32 = (void *)TSMuxBusPoke32,
  .BitGet8 = (void *)TSMuxBusBitGet8,
  .BitAssign8 = (void *)TSMuxBusBitAssign8,
  .BitSet8 = (void *)TSMuxBusBitSet8,
  .BitClear8 = (void *)TSMuxBusBitClear8,
  .BitGet16 = (void *)TSMuxBusBitGet16,
  .BitAssign16 = (void *)TSMuxBusBitAssign16,
  .BitSet16 = (void *)TSMuxBusBitSet16,
  .BitClear16 = (void *)TSMuxBusBitClear16,
  .BitGet32 = (void *)TSMuxBusBitGet32,
  .BitAssign32 = (void *)TSMuxBusBitAssign32,
  .BitSet32 = (void *)TSMuxBusBitSet32,
  .BitClear32 = (void *)TSMuxBusBitClear32,
  .PeekStream = (void *)TSMuxBusPeekStream,
  .PokeStream = (void *)TSMuxBusPokeStream,
  .Refresh = (void *)TSMuxBusRefresh,
  .Commit = (void *)TSMuxBusCommit,
  .BitToggle8 = (void *)TSMuxBusBitToggle8,
  .BitToggle16 = (void *)TSMuxBusBitToggle16,
  .BitToggle32 = (void *)TSMuxBusBitToggle32,
  .Assign8X = (void *)TSMuxBusAssign8X,
  .Assign16X = (void *)TSMuxBusAssign16X,
  .Assign32X = (void *)TSMuxBusAssign32X,
  .BitsGet8 = (void *)TSMuxBusBitsGet8,
  .BitsGet16 = (void *)TSMuxBusBitsGet16,
  .BitsGet32 = (void *)TSMuxBusBitsGet32
};

// cadrs = 0x20 for TS-4200
void *TSMuxBusInit(TSMuxBus *bus,void *configbus,int cadrs,void *regbus8, int base8, void *regbus16, int base16) {
  if (bus->InitStatus > 0) return bus;

  bus->Init = (void *)TSMuxBusInit;
  bus->Fini = (void *)TSMuxBusFini;
  bus->Lock = (void *)TSMuxBusLock;
  bus->Unlock = (void *)TSMuxBusUnlock;
  bus->Preempt = (void *)TSMuxBusPreempt;
  bus->Peek8 = (void *)TSMuxBusPeek8;
  bus->Poke8 = (void *)TSMuxBusPoke8;
  bus->Peek16 = (void *)TSMuxBusPeek16;
  bus->Poke16 = (void *)TSMuxBusPoke16;
  bus->Peek32 = (void *)TSMuxBusPeek32;
  bus->Poke32 = (void *)TSMuxBusPoke32;
  bus->BitGet8 = (void *)TSMuxBusBitGet8;
  bus->BitAssign8 = (void *)TSMuxBusBitAssign8;
  bus->BitSet8 = (void *)TSMuxBusBitSet8;
  bus->BitClear8 = (void *)TSMuxBusBitClear8;
  bus->BitGet16 = (void *)TSMuxBusBitGet16;
  bus->BitAssign16 = (void *)TSMuxBusBitAssign16;
  bus->BitSet16 = (void *)TSMuxBusBitSet16;
  bus->BitClear16 = (void *)TSMuxBusBitClear16;
  bus->BitGet32 = (void *)TSMuxBusBitGet32;
  bus->BitAssign32 = (void *)TSMuxBusBitAssign32;
  bus->BitSet32 = (void *)TSMuxBusBitSet32;
  bus->BitClear32 = (void *)TSMuxBusBitClear32;
  bus->PeekStream = (void *)TSMuxBusPeekStream;
  bus->PokeStream = (void *)TSMuxBusPokeStream;
  bus->Refresh = (void *)TSMuxBusRefresh;
  bus->Commit = (void *)TSMuxBusCommit;
  bus->BitToggle8 = (void *)TSMuxBusBitToggle8;
  bus->BitToggle16 = (void *)TSMuxBusBitToggle16;
  bus->BitToggle32 = (void *)TSMuxBusBitToggle32;
  bus->Assign8X = (void *)TSMuxBusAssign8X;
  bus->Assign16X = (void *)TSMuxBusAssign16X;
  bus->Assign32X = (void *)TSMuxBusAssign32X;
  bus->BitsGet8 = (void *)TSMuxBusBitsGet8;
  bus->BitsGet16 = (void *)TSMuxBusBitsGet16;
  bus->BitsGet32 = (void *)TSMuxBusBitsGet32;

  TSMuxBusLockInit(bus,1);
  bus->configbus = configbus;
  assert(bus->configbus);
  bus->regbus8 = regbus8;
  bus->regbus16 = regbus16;
  bus->cadrs = cadrs;
  bus->base8 = base8;
  bus->base16 = base16;
  if (bus->configbus->InitStatus <= 0
      || bus->regbus8->InitStatus <= 0
      || bus->regbus16->InitStatus <= 0) {
    bus->Fini(bus);
    bus->InitStatus = -1;
    return bus;
  }
  bus->InitStatus = 1;
  return bus;
}

void TSMuxBusFini(TSMuxBus *bus) {
  assert(bus->configbus);
  bus->configbus->Fini(bus->configbus);
  bus->regbus8->Fini(bus->regbus8);
  bus->regbus16->Fini(bus->regbus16);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

void TSMuxBusRefresh(TSMuxBus *bus) {
  // nothing to do
}

void TSMuxBusCommit(TSMuxBus *bus,int forceall) {
  // nothing to do
}

void TSMuxBusPeekStream(TSMuxBus *bus,int adr,int dir,char* buf) {
  // TO DO: support this function
}

void TSMuxBusPokeStream(TSMuxBus *bus,int adr,int dir,const char* buf) {
  // TO DO: support this function
}


//-----------------------------------------------------------------------------
static inline unsigned char _TSMuxBusPeek8(TSMuxBus *bus,int adrs) {
  return bus->regbus8->Peek8(bus->regbus8,adrs+bus->base8);
}

static inline void _TSMuxBusPoke8(TSMuxBus *bus,int adrs,unsigned char val) {
  bus->regbus8->Poke8(bus->regbus8,adrs+bus->base8,val);
}

// note: adrs & 1 != 0 not supported
static inline unsigned short _TSMuxBusPeek16(TSMuxBus *bus,int adrs) {
  return bus->regbus16->Peek16(bus->regbus16,adrs+bus->base16);
}

static inline void _TSMuxBusPoke16(TSMuxBus *bus,int adrs,unsigned short val) {
  bus->regbus16->Poke16(bus->regbus16,adrs+bus->base16,val);
}

static inline unsigned _TSMuxBusPeek32(TSMuxBus *bus,int adrs) {
  return 0;
}

static inline void _TSMuxBusPoke32(TSMuxBus *bus,int adrs,unsigned val) {
}
//-----------------------------------------------------------------------------
DefinitionFunctionsBit(TSMuxBus,unsigned char,8)
DefinitionFunctionsBit(TSMuxBus,unsigned short,16)
DefinitionFunctionsBit(TSMuxBus,unsigned,32)

#endif
