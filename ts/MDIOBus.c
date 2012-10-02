#include "MDIOBus.h"
#include "Bit.h"

static BusAPI MDIOBusAPI = {
  .Init = (void *)MDIOBusInit,
  .Fini = (void *)MDIOBusFini,
  .Lock = (void *)MDIOBusLock,
  .Peek8 = (void *)MDIOBusPeek8,
  .Poke8 = (void *)MDIOBusPoke8,
  .Peek16 = (void *)MDIOBusPeek16,
  .Poke16 = (void *)MDIOBusPoke16,
  .Peek32 = (void *)MDIOBusPeek32,
  .Poke32 = (void *)MDIOBusPoke32,
  .BitGet8 = (void *)MDIOBusBitGet8,
  .BitAssign8 = (void *)MDIOBusBitAssign8,
  .BitSet8 = (void *)MDIOBusBitSet8,
  .BitClear8 = (void *)MDIOBusBitClear8,
  .BitGet16 = (void *)MDIOBusBitGet16,
  .BitAssign16 = (void *)MDIOBusBitAssign16,
  .BitSet16 = (void *)MDIOBusBitSet16,
  .BitClear16 = (void *)MDIOBusBitClear16,
  .BitGet32 = (void *)MDIOBusBitGet32,
  .BitAssign32 = (void *)MDIOBusBitAssign32,
  .BitSet32 = (void *)MDIOBusBitSet32,
  .BitClear32 = (void *)MDIOBusBitClear32,
  .PeekStream = (void *)MDIOBusPeekStream,
  .PokeStream = (void *)MDIOBusPokeStream,
  .Refresh = (void *)MDIOBusRefresh,
  .Commit = (void *)MDIOBusCommit,
  .BitToggle8 = (void *)MDIOBusBitToggle8,
  .BitToggle16 = (void *)MDIOBusBitToggle16,
  .BitToggle32 = (void *)MDIOBusBitToggle32,
  .Assign8X = (void *)MDIOBusAssign8X,
  .Assign16X = (void *)MDIOBusAssign16X,
  .Assign32X = (void *)MDIOBusAssign32X,
  .BitsGet8 = (void *)MDIOBusBitsGet8,
  .BitsGet16 = (void *)MDIOBusBitsGet16,
  .BitsGet32 = (void *)MDIOBusBitsGet32
};

void *MDIOBusInit(MDIOBus *bus,void *dio,void *time,int MDC,int MDIO,unsigned delay) {
  if (bus->InitStatus > 0) return bus;
  bus->API = &MDIOBusAPI;
  bus->dio = dio;
  bus->time = time;
  if (bus->dio->InitStatus < 0
      || bus->time->InitStatus < 0) {
    bus->Fini(bus);
    bus->InitStatus = -1;
    return bus;
  }
  bus->MDC = MDC;
  bus->MDIO = MDIO;
  bus->delay = delay;
  bus->InitStatus = 1;
  return bus;
}

void MDIOBusFini(MDIOBus *bus) {
  bus->dio->Fini(bus->dio);
  bus->time->Fini(bus->time);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

int MDIOBusLock(MDIOBus *bus,int command,unsigned num) {
  return 1;
}

void MDIOBusRefresh(MDIOBus *bus) {
  // nothing to do
}

void MDIOBusCommit(MDIOBus *bus,int forceall) {
  // nothing to do
}

//-----------------------------------------------------------------------------

static inline unsigned char _MDIOBusPeek8(MDIOBus *bus,int adrs) {
  return 0; // only 16-bit supported
}

static inline void _MDIOBusPoke8(MDIOBus *bus,int adrs,unsigned char val) {
  // only 16-bit supported
}


static inline void _MDIOOut(MDIOBus *bus,DIOState state) {
  static DIOState last_state = -99;
  // entry: MDC low
  // exit: MDC low
  if (state != last_state) {
    bus->dio->SetAsync(bus->dio,bus->MDIO,state);
    last_state = state;
  }
  bus->time->Wait(bus->time,bus->delay);
  bus->dio->SetAsync(bus->dio,bus->MDC,HIGH);
  bus->time->Wait(bus->time,bus->delay);
  bus->dio->SetAsync(bus->dio,bus->MDC,LOW);
}

static inline int _MDIOIn(MDIOBus *bus) {
  int ret;
  // entry: MDC low, MDIO input
  // exit: MDC low, MDIO input
  bus->time->Wait(bus->time,bus->delay);
  ret = (bus->dio->GetAsync(bus->dio,bus->MDIO) == INPUT_HIGH) ? 1 : 0;
  bus->dio->SetAsync(bus->dio,bus->MDC,HIGH);
  bus->time->Wait(bus->time,bus->delay);
  bus->dio->SetAsync(bus->dio,bus->MDC,LOW);
}

static unsigned short _MDIOPeekPoke(MDIOBus *bus,int adrs,int read,int value) {
  int i;

  bus->dio->Lock(bus->dio,WaitLock,bus->MDC);
  bus->dio->Lock(bus->dio,WaitLock,bus->MDIO);
  bus->dio->SetAsync(bus->dio,bus->MDC,LOW);
  // preamble
  for (i=0;i<32;i++) {
    _MDIOOut(bus,HIGH);
  }
  // START
  _MDIOOut(bus,LOW);
  _MDIOOut(bus,HIGH);
  // R/W
  _MDIOOut(bus,read?HIGH:LOW);
  _MDIOOut(bus,read?LOW:HIGH);
  // PHY address is adrs[9:5]
  // REG address is adrs[4:0]
  for (i=9;i>=0;i--) {
    _MDIOOut(bus,(adrs >> i)?HIGH:LOW);
  }
  // turn-around / wait
  _MDIOOut(bus,read?INPUT:HIGH);
  _MDIOOut(bus,read?INPUT:LOW);
  // read or write the data
  if (!read) {
    for (i=15;i>=0;i--) {
      _MDIOOut(bus,(value >> i)?HIGH:LOW);
    }
  } else {
    value = 0;
    for (i=15;i>=0;i--) {
      value = (value << 1) + _MDIOIn(bus);
    }
  }
  bus->dio->Lock(bus->dio,DoRelease,bus->MDC);
  bus->dio->Lock(bus->dio,DoRelease,bus->MDIO);
  return value;
}

static inline unsigned short _MDIOBusPeek16(MDIOBus *bus,int adrs) {
  return _MDIOPeekPoke(bus,adrs,1,0);
}

static inline void _MDIOBusPoke16(MDIOBus *bus,int adrs,unsigned short val) {
  _MDIOPeekPoke(bus,adrs,0,val);
}

static inline unsigned _MDIOBusPeek32(MDIOBus *bus,int adrs) {
  return 0; // only 16-bit supported
}

static inline void _MDIOBusPoke32(MDIOBus *bus,int adrs,unsigned val) {
  // only 16-bit supported
}
//-----------------------------------------------------------------------------
DefinitionFunctionsBit(MDIOBus,unsigned char,8)
DefinitionFunctionsBit(MDIOBus,unsigned short,16)
DefinitionFunctionsBit(MDIOBus,unsigned,32)

void MDIOBusPeekStream(MDIOBus *bus,int adr,int dir,char *buf,int len) {
  int i;
  for (i=0;i<len;i++) {
    buf[i] = _MDIOBusPeek8(bus,adr);
    adr += dir;
  }
}

void MDIOBusPokeStream(MDIOBus *bus,int adr,int dir,char *buf,int len) {
  int i;
  for (i=0;i<len;i++) {
    _MDIOBusPoke8(bus,adr,buf[i]);
    adr += dir;
  }
}
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
