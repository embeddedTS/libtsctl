#ifndef WindowBus_c
#define WindowBus_c
#include "WindowBus.h"
#include "Bit.h"

#define LOCK_TYPE_SHARED
#define LOCK_CLASS WindowBus
#include "TSLock.h"

void *WindowBusInit(WindowBus *bus,void *sub,int adrs,int data) {
  if (bus->InitStatus > 0) return bus;
  bus->sub = sub;
  bus->adrs = adrs;
  bus->data = data;

  if (bus->sub->InitStatus < 0) {
    bus->Fini(bus);
    bus->InitStatus = -1;
    return bus;
  }
  bus->Init = (void *)WindowBusInit;
  bus->Fini = (void *)WindowBusFini;
  bus->Lock = (void *)WindowBusLock;
  bus->Unlock = (void *)WindowBusUnlock;
  bus->Preempt = (void *)WindowBusPreempt;
  bus->Peek8 = (void *)WindowBusPeek8;
  bus->Poke8 = (void *)WindowBusPoke8;
  bus->Peek16 = (void *)WindowBusPeek16;
  bus->Poke16 = (void *)WindowBusPoke16;
  bus->Peek32 = (void *)WindowBusPeek32;
  bus->Poke32 = (void *)WindowBusPoke32;
  bus->BitGet8 = (void *)WindowBusBitGet8;
  bus->BitAssign8 = (void *)WindowBusBitAssign8;
  bus->BitSet8 = (void *)WindowBusBitSet8;
  bus->BitClear8 = (void *)WindowBusBitClear8;
  bus->BitGet16 = (void *)WindowBusBitGet16;
  bus->BitAssign16 = (void *)WindowBusBitAssign16;
  bus->BitSet16 = (void *)WindowBusBitSet16;
  bus->BitClear16 = (void *)WindowBusBitClear16;
  bus->BitGet32 = (void *)WindowBusBitGet32;
  bus->BitAssign32 = (void *)WindowBusBitAssign32;
  bus->BitSet32 = (void *)WindowBusBitSet32;
  bus->BitClear32 = (void *)WindowBusBitClear32;
  bus->PeekStream = (void *)WindowBusPeekStream;
  bus->PokeStream = (void *)WindowBusPokeStream;
  bus->Refresh = (void *)WindowBusRefresh;
  bus->Commit = (void *)WindowBusCommit;
  bus->BitToggle8 = (void *)WindowBusBitToggle8;
  bus->BitToggle16 = (void *)WindowBusBitToggle16;
  bus->BitToggle32 = (void *)WindowBusBitToggle32;
  bus->Assign8X = (void *)WindowBusAssign8X;
  bus->Assign16X = (void *)WindowBusAssign16X;
  bus->Assign32X = (void *)WindowBusAssign32X;
  bus->BitsGet8 = (void *)WindowBusBitsGet8;
  bus->BitsGet16 = (void *)WindowBusBitsGet16;
  bus->BitsGet32 = (void *)WindowBusBitsGet32;
  bus->InitStatus = 1;
  return bus;
}

void WindowBusFini(WindowBus *bus) {
  bus->sub->Fini(bus->sub);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

static unsigned char _WindowBusPeek8(WindowBus *bus,int adr) {
  unsigned char ret;

  bus->sub->Lock(bus->sub,0,SHARED);
  bus->sub->Poke8(bus->sub,bus->adrs,adr);
  ret = bus->sub->Peek8(bus->sub,bus->data) & 0xFF;
  bus->sub->Unlock(bus->sub,0,SHARED);
  return ret;
}

static void _WindowBusPoke8(WindowBus *bus,int adr, unsigned char dat) {
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke8(bus->sub,bus->adrs,adr);
  bus->sub->Poke8(bus->sub,bus->data,dat);
  bus->sub->Unlock(bus->sub,0,0);
}

static unsigned short _WindowBusPeek16(WindowBus *bus,int adr) {
  return 0; // unsupported
}

static void _WindowBusPoke16(WindowBus *bus,int adr, unsigned short dat) {
  // unsupported
}

static unsigned _WindowBusPeek32(WindowBus *bus,int adr) {
  // unsupported
}

static void _WindowBusPoke32(WindowBus *bus,int adr, unsigned dat) {
  // unsupported
}

void WindowBusPeekStream(WindowBus *bus,int adr,int dir,char* buf) {
  int len = ArrayLength(buf);
  bus->sub->Lock(bus->sub,0,SHARED);
  bus->sub->Poke8(bus->sub,bus->adrs,adr);
  while (len > 0) {
    *buf++ = bus->sub->Peek8(bus->sub,bus->data);
    len --;
  }
  bus->sub->Unlock(bus->sub,0,SHARED);
}

void WindowBusPokeStream(WindowBus *bus,int adr,int dir,const char* buf) {
  int len = ArrayLength(buf);
  bus->sub->Lock(bus->sub,0,0);
  bus->sub->Poke8(bus->sub,bus->adrs,adr);
  while (len > 0) {
    bus->sub->Poke8(bus->sub,bus->data, *buf++);
    len --;
  }
  bus->sub->Unlock(bus->sub,0,0);
}

void WindowBusRefresh(WindowBus *bus) {
  bus->sub->Refresh(bus->sub);
}

void WindowBusCommit(WindowBus *bus,int forceall) {
  bus->sub->Commit(bus->sub,forceall);
}

DefinitionFunctionsBit(WindowBus,unsigned char,8)
DefinitionFunctionsBit(WindowBus,unsigned short,16)
DefinitionFunctionsBit(WindowBus,unsigned,32)
#endif
