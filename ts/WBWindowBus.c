#ifndef WBWindowBus_c
#define WBWindowBus_c
#include "WBWindowBus.h"
#include "Bit.h"
#include "Array.h"

void *WBWindowBusInit(WBWindowBus *bus,void *sub,int adrs,int offset) {
  if (bus->InitStatus > 0) return bus;
  bus->sub = sub;
  bus->adrs = adrs;
  bus->offset = offset;

  if (bus->sub->InitStatus < 0) {
    bus->Fini(bus);
    bus->InitStatus = -1;
    return bus;
  }
  bus->Init = (void *)WBWindowBusInit;
  bus->Fini = (void *)WBWindowBusFini;
  bus->Lock = (void *)WBWindowBusLock;
  bus->Unlock = (void *)WBWindowBusUnlock;
  bus->Preempt = (void *)WBWindowBusPreempt;
  bus->Peek8 = (void *)WBWindowBusPeek8;
  bus->Poke8 = (void *)WBWindowBusPoke8;
  bus->Peek16 = (void *)WBWindowBusPeek16;
  bus->Poke16 = (void *)WBWindowBusPoke16;
  bus->Peek32 = (void *)WBWindowBusPeek32;
  bus->Poke32 = (void *)WBWindowBusPoke32;
  bus->BitGet8 = (void *)WBWindowBusBitGet8;
  bus->BitAssign8 = (void *)WBWindowBusBitAssign8;
  bus->BitSet8 = (void *)WBWindowBusBitSet8;
  bus->BitClear8 = (void *)WBWindowBusBitClear8;
  bus->BitGet16 = (void *)WBWindowBusBitGet16;
  bus->BitAssign16 = (void *)WBWindowBusBitAssign16;
  bus->BitSet16 = (void *)WBWindowBusBitSet16;
  bus->BitClear16 = (void *)WBWindowBusBitClear16;
  bus->BitGet32 = (void *)WBWindowBusBitGet32;
  bus->BitAssign32 = (void *)WBWindowBusBitAssign32;
  bus->BitSet32 = (void *)WBWindowBusBitSet32;
  bus->BitClear32 = (void *)WBWindowBusBitClear32;
  bus->PeekStream = (void *)WBWindowBusPeekStream;
  bus->PokeStream = (void *)WBWindowBusPokeStream;
  bus->Refresh = (void *)WBWindowBusRefresh;
  bus->Commit = (void *)WBWindowBusCommit;
  bus->BitToggle8 = (void *)WBWindowBusBitToggle8;
  bus->BitToggle16 = (void *)WBWindowBusBitToggle16;
  bus->BitToggle32 = (void *)WBWindowBusBitToggle32;
  bus->Assign8X = (void *)WBWindowBusAssign8X;
  bus->Assign16X = (void *)WBWindowBusAssign16X;
  bus->Assign32X = (void *)WBWindowBusAssign32X;
  bus->BitsGet8 = (void *)WBWindowBusBitsGet8;
  bus->BitsGet16 = (void *)WBWindowBusBitsGet16;
  bus->BitsGet32 = (void *)WBWindowBusBitsGet32;
  bus->InitStatus = 1;
  return bus;
}

void WBWindowBusFini(WBWindowBus *bus) {
  bus->sub->Fini(bus->sub);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

int WBWindowBusLock(WBWindowBus *bus,unsigned num,int flags) {
  return 1;
}
int WBWindowBusUnlock(WBWindowBus *bus,unsigned num,int flags) {
  return 1;
}
int WBWindowBusPreempt(WBWindowBus *bus) {
  return 1;
}

static unsigned char _WBWindowBusPeek8(WBWindowBus *bus,int adr) {
  unsigned char ret;

  adr += bus->offset;
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke16(bus->sub,bus->adrs,adr>>11);
  bus->sub->Poke16(bus->sub,bus->adrs+2,0xC000+(adr & 0x7FF));
  ret = bus->sub->Peek16(bus->sub,bus->adrs+4) & 0xFF;
  bus->sub->Unlock(bus->sub,0,0);
  return ret;
}

static void _WBWindowBusPoke8(WBWindowBus *bus,int adr, unsigned char dat) {
  adr += bus->offset;
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke16(bus->sub,bus->adrs,adr>>11);
  bus->sub->Poke16(bus->sub,bus->adrs+2,0xC000+(adr & 0x7FF));
  bus->sub->Poke16(bus->sub,bus->adrs+4,dat);
  bus->sub->Unlock(bus->sub,0,0);
}

static unsigned short _WBWindowBusPeek16(WBWindowBus *bus,int adr) {
  unsigned short ret;

  adr += bus->offset;
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke16(bus->sub,bus->adrs,adr>>11);
  bus->sub->Poke16(bus->sub,bus->adrs+2,0x8000+(adr & 0x7FF));
  ret = bus->sub->Peek16(bus->sub,bus->adrs+4);
  bus->sub->Unlock(bus->sub,0,0);
  return ret;
}

static void _WBWindowBusPoke16(WBWindowBus *bus,int adr, unsigned short dat) {
  adr += bus->offset;
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke16(bus->sub,bus->adrs,adr>>11);
  bus->sub->Poke16(bus->sub,bus->adrs+2,0x8000+(adr & 0x7FF));
  bus->sub->Poke16(bus->sub,bus->adrs+4,dat);
  bus->sub->Unlock(bus->sub,0,0);
}

static unsigned _WBWindowBusPeek32(WBWindowBus *bus,int adr) {
  unsigned ret;

  adr += bus->offset;
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke16(bus->sub,bus->adrs,adr>>11);
  bus->sub->Poke16(bus->sub,bus->adrs+2,0x6000+(adr & 0x7FF));
  ret = bus->sub->Peek16(bus->sub,bus->adrs+4);
  ret += (bus->sub->Peek16(bus->sub,bus->adrs+4) >> 16);
  bus->sub->Unlock(bus->sub,0,0);
  return ret;
}

static void _WBWindowBusPoke32(WBWindowBus *bus,int adr, unsigned dat) {
  adr += bus->offset;
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke16(bus->sub,bus->adrs,adr>>11);
  bus->sub->Poke16(bus->sub,bus->adrs+2,0x6000+(adr & 0x7FF));
  bus->sub->Poke16(bus->sub,bus->adrs+4,dat & 0xFFFF);
  bus->sub->Poke16(bus->sub,bus->adrs+4,dat >> 16);
  bus->sub->Unlock(bus->sub,0,0);
}

void WBWindowBusPeekStream(WBWindowBus *bus,int adr,int dir,char* buf) {
  int len = ArrayLength(buf);
  adr += bus->offset;
  // TO DO: optimize using split mode
  bus->sub->Lock(bus->sub,0,0);
  while (len > 0) {
    *buf++ = bus->sub->Peek8(bus->sub,adr);
    len --;
    adr += dir;
  }
  bus->sub->Unlock(bus->sub,0,0);
}

void WBWindowBusPokeStream(WBWindowBus *bus,int adr,int dir,const char* buf) {
  int len = ArrayLength(buf);
  adr += bus->offset;
  // TO DO: optimize using split mode
  bus->sub->Lock(bus->sub,0,0);
  while (len > 0) {
    bus->sub->Poke8(bus->sub,adr, *buf++);
    adr += dir;
    len --;
  }
  bus->sub->Unlock(bus->sub,0,0);
}

void WBWindowBusRefresh(WBWindowBus *bus) {
  bus->sub->Refresh(bus->sub);
}

void WBWindowBusCommit(WBWindowBus *bus,int forceall) {
  bus->sub->Commit(bus->sub,forceall);
}

DefinitionFunctionsBit(WBWindowBus,unsigned char,8)
DefinitionFunctionsBit(WBWindowBus,unsigned short,16)
DefinitionFunctionsBit(WBWindowBus,unsigned,32)
#endif
