#ifndef CacheBus_c
#define CacheBus_c
#include <stdio.h>
#include <stdlib.h>
#include "Bit.h"
#include "CacheBus.h"
/*
  BusCache module

  This module caches access to a bus.  It was initially designed for
  optimizing access to DIOs which are accessed across a slow bus such
  as SBus.  It has expanded to provide the implementation for synchronous
  DIOs.
 */

#define LOCK_TYPE_SHARED_DEFERRED
#define LOCK_CLASS CacheBus
#include "TSLock.h"

static BusAPI CacheBusAPI = {
  .Init = (void *)CacheBusInit,
  .Fini = (void *)CacheBusFini,
  .Lock = (void *)CacheBusLock,
  .Unlock = (void *)CacheBusUnlock,
  .Preempt = (void *)CacheBusPreempt,
  .Peek8 = (void *)CacheBusPeek8,
  .Poke8 = (void *)CacheBusPoke8,
  .Peek16 = (void *)CacheBusPeek16,
  .Poke16 = (void *)CacheBusPoke16,
  .Peek32 = (void *)CacheBusPeek32,
  .Poke32 = (void *)CacheBusPoke32,
  .BitGet8 = (void *)CacheBusBitGet8,
  .BitAssign8 = (void *)CacheBusBitAssign8,
  .BitSet8 = (void *)CacheBusBitSet8,
  .BitClear8 = (void *)CacheBusBitClear8,
  .BitGet16 = (void *)CacheBusBitGet16,
  .BitAssign16 = (void *)CacheBusBitAssign16,
  .BitSet16 = (void *)CacheBusBitSet16,
  .BitClear16 = (void *)CacheBusBitClear16,
  .BitGet32 = (void *)CacheBusBitGet32,
  .BitAssign32 = (void *)CacheBusBitAssign32,
  .BitSet32 = (void *)CacheBusBitSet32,
  .BitClear32 = (void *)CacheBusBitClear32,
  .PeekStream = (void *)CacheBusPeekStream,
  .PokeStream = (void *)CacheBusPokeStream,
  .Refresh = (void *)CacheBusRefresh,
  .Commit = (void *)CacheBusCommit,
  .BitToggle8 = (void *)CacheBusBitToggle8,
  .BitToggle16 = (void *)CacheBusBitToggle16,
  .BitToggle32 = (void *)CacheBusBitToggle32,
  .Assign8X = (void *)CacheBusAssign8X,
  .Assign16X = (void *)CacheBusAssign16X,
  .Assign32X = (void *)CacheBusAssign32X,
  .BitsGet8 = (void *)CacheBusBitsGet8,
  .BitsGet16 = (void *)CacheBusBitsGet16,
  .BitsGet32 = (void *)CacheBusBitsGet32
};

void *CacheBusInit(CacheBus *bus,void *bus1) {
  Bus *sub = bus1;
  int i,j,err=0;
  char str[32];

  if (bus->InitStatus > 0) return bus;

  bus->Init = (void *)CacheBusInit;
  bus->Fini = (void *)CacheBusFini;
  bus->Lock = (void *)CacheBusLock;
  bus->Unlock = (void *)CacheBusUnlock;
  bus->Preempt = (void *)CacheBusPreempt;
  bus->Peek8 = (void *)CacheBusPeek8;
  bus->Poke8 = (void *)CacheBusPoke8;
  bus->Peek16 = (void *)CacheBusPeek16;
  bus->Poke16 = (void *)CacheBusPoke16;
  bus->Peek32 = (void *)CacheBusPeek32;
  bus->Poke32 = (void *)CacheBusPoke32;
  bus->BitGet8 = (void *)CacheBusBitGet8;
  bus->BitAssign8 = (void *)CacheBusBitAssign8;
  bus->BitSet8 = (void *)CacheBusBitSet8;
  bus->BitClear8 = (void *)CacheBusBitClear8;
  bus->BitGet16 = (void *)CacheBusBitGet16;
  bus->BitAssign16 = (void *)CacheBusBitAssign16;
  bus->BitSet16 = (void *)CacheBusBitSet16;
  bus->BitClear16 = (void *)CacheBusBitClear16;
  bus->BitGet32 = (void *)CacheBusBitGet32;
  bus->BitAssign32 = (void *)CacheBusBitAssign32;
  bus->BitSet32 = (void *)CacheBusBitSet32;
  bus->BitClear32 = (void *)CacheBusBitClear32;
  bus->PeekStream = (void *)CacheBusPeekStream;
  bus->PokeStream = (void *)CacheBusPokeStream;
  bus->Refresh = (void *)CacheBusRefresh;
  bus->Commit = (void *)CacheBusCommit;
  bus->BitToggle8 = (void *)CacheBusBitToggle8;
  bus->BitToggle16 = (void *)CacheBusBitToggle16;
  bus->BitToggle32 = (void *)CacheBusBitToggle32;
  bus->Assign8X = (void *)CacheBusAssign8X;
  bus->Assign16X = (void *)CacheBusAssign16X;
  bus->Assign32X = (void *)CacheBusAssign32X;
  bus->BitsGet8 = (void *)CacheBusBitsGet8;
  bus->BitsGet16 = (void *)CacheBusBitsGet16;
  bus->BitsGet32 = (void *)CacheBusBitsGet32;

  CacheBusLockInit(bus);
  bus->sub = sub;
  if (bus->sub->InitStatus <= 0) {
    bus->InitStatus = -1;
    return bus;
  }
  if (bus->Width != 8 && bus->Width != 16 && bus->Width != 32) {
    bus->InitStatus = CacheBusErrorWidthInvalid;
    return bus;
  }
  // Initialize cache
  bus->sub->Lock(bus->sub,0,0);
  if (bus->Width == 8) {
    for (i=0;i<bus->Length;i++) {
      if (bus->OBit[i] | bus->IBit[i]) {
	bus->icache[i] = bus->ocache[i] = bus->sub->Peek8(bus->sub,i+bus->Offset);
	bus->ocache0[i] = ~bus->ocache[i]; // FIX? was ocache0
      } else bus->icache[i] = bus->ocache0[i] = 0;
    }
  } else if (bus->Width == 16) {
    for (i=0,j=0;i<bus->Length;i++,j+=2) {
      if (bus->OBit[i] | bus->IBit[i]) {
	bus->icache[i] = bus->ocache[i] = bus->sub->Peek16(bus->sub,j+bus->Offset);
	bus->ocache0[i] = ~bus->ocache[i]; // FIX? was ocache0
      } else bus->icache[i] = bus->ocache0[i] = 0;
    }
  } else { // bus->Width == 32
    for (i=0,j=0;i<bus->Length;i++,j+=4) {
      if (bus->OBit[i] | bus->IBit[i]) {
	bus->icache[i] = bus->ocache[i] = bus->sub->Peek32(bus->sub,j+bus->Offset);
	bus->ocache0[i] = ~bus->ocache[i]; // FIX? was ocache0
      } else bus->icache[i] = bus->ocache0[i] = 0;
    }
  }
  bus->sub->Unlock(bus->sub,0,0);
  bus->InitStatus = 1;
  return bus;
}

void CacheBusFini(CacheBus *bus) {
  bus->sub->Fini(bus->sub);
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

void CacheBusRefresh(CacheBus *bus) {
  int i,j;

  CacheBusLockReal(bus,SHARED);
  if (bus->Width == 8) {
    for (i=0;i<bus->Length;i++) {
      if (bus->IBit[i]) {
	if (i == 0) fprintf(stderr, "Refresh was %X ",bus->ocache[i]);
	bus->ocache[i] = bus->icache[i] = bus->sub->Peek8(bus->sub,i+bus->Offset);
	if (i == 0) fprintf(stderr, "now %X ",bus->ocache[i]);
      }
    }
  } else if (bus->Width == 16) {
    for (i=0,j=0;i<bus->Length;i++,j+=2) {
      if (bus->IBit[i]) {
	bus->ocache[i] = bus->icache[i] = bus->sub->Peek16(bus->sub,j+bus->Offset);
      }
    }
  } else { // bus->Width == 32
    for (i=0,j=0;i<bus->Length;i++,j+=4) {
      if (bus->IBit[i]) {
	bus->ocache[i] = bus->icache[i] = bus->sub->Peek32(bus->sub,j+bus->Offset);
      }
    }
  }
  //bus->sub->Lock(bus->sub,DoRelease,0);
}


void CacheBusCommit(CacheBus *bus,int forceall) {
  int i,j;

  CacheBusLockReal(bus,0);
  if (bus->Width == 8) {
    for (i=0;i<bus->Length;i++) {
      if  (forceall || (bus->ocache[i] ^ bus->ocache0[i]) & bus->OBit[i]) {
	bus->sub->Poke8(bus->sub,i+bus->Offset,bus->ocache[i]);
	if (bus->WO) bus->icache[i] &= ~bus->WO[i];
	if (bus->WO) bus->ocache[i] &= ~bus->WO[i];
	bus->ocache0[i] = bus->ocache[i];
      }
    }
  } else if (bus->Width == 16) {
    for (i=0,j=0;i<bus->Length;i++,j+=2) {
      /*
      if (i==0) fprintf(stderr,"%X %X %X :%X\n",
			bus->ocache[i], bus->ocache0[i], bus->OBit[i],
			(bus->ocache[i] ^ bus->ocache0[i]) & bus->OBit[i]);
      */
      if  (forceall || (bus->ocache[i] ^ bus->ocache0[i]) & bus->OBit[i]) {
	//fprintf(stderr,"%d:%X\n",i,bus->ocache[i]);
	bus->sub->Poke16(bus->sub,j+bus->Offset,bus->ocache[i]);
	if (bus->WO) bus->icache[i] &= ~bus->WO[i];
	if (bus->WO) bus->ocache[i] &= ~bus->WO[i];
	bus->ocache0[i] = bus->ocache[i];
      }
    }
    //fprintf(stderr,"\n");
  } else { // bus->Width == 32
    for (i=0,j=0;i<bus->Length;i++,j+=4) {
      if  (forceall || (bus->ocache[i] ^ bus->ocache0[i]) & bus->OBit[i]) {
	bus->sub->Poke32(bus->sub,j+bus->Offset,bus->ocache[i]);
	if (bus->WO) bus->icache[i] &= ~bus->WO[i];
	if (bus->WO) bus->ocache[i] &= ~bus->WO[i];
	bus->ocache0[i] = bus->ocache[i];
      }
    }
  }
  //bus->sub->Lock(bus->sub,DoRelease,0);
}

// These functions currently aren't cachable
void CacheBusPeekStream(CacheBus *bus,int adr,int dir,char* buf) {
  CacheBusLockReal(bus,SHARED);
  bus->sub->PeekStream(bus->sub,adr,dir,buf);
}

void CacheBusPokeStream(CacheBus *bus,int adr,int dir,const char* buf) {
  CacheBusLockReal(bus,0);
  bus->sub->PokeStream(bus->sub,adr,dir,buf);
}

//-----------------------------------------------------------------------------
static inline unsigned char _CacheBusPeek8(CacheBus *bus,int adrs){
  if (bus->Width == 8 && adrs < 0 
      && ~adrs >= bus->Offset && ~adrs < bus->Offset + bus->Length) {
    return bus->icache[~adrs-bus->Offset];
  } else {
    if (adrs < 0) adrs = ~adrs;
    CacheBusLockReal(bus,SHARED);
    return bus->sub->Peek8(bus->sub,adrs);
  }
}

static inline void _CacheBusPoke8(CacheBus *bus,int adrs,unsigned char val){
  if (bus->Width == 8  && adrs < 0 
      && ~adrs >= bus->Offset && ~adrs < bus->Offset + bus->Length) {
    bus->ocache[~adrs-bus->Offset] = val;
    bus->icache[~adrs-bus->Offset] = 
      bus->icache[~adrs-bus->Offset] & ~bus->OBit[~adrs-bus->Offset] 
      | val & bus->OBit[~adrs-bus->Offset];
  } else {
    if (adrs < 0) adrs = ~adrs;
    CacheBusLockReal(bus,0);
    return bus->sub->Poke8(bus->sub,adrs,val);
  }
}

static inline unsigned short _CacheBusPeek16(CacheBus *bus,int adrs){
  if (bus->Width == 16 && adrs < 0
      && ~adrs >= bus->Offset && ~adrs < bus->Offset + 2*bus->Length) {
    //fprintf(stderr,"N1:%X->%X\n",~adrs,bus->icache[(~adrs-bus->Offset)/2]);
    return bus->icache[(~adrs-bus->Offset)/2];
  } else {
    unsigned short val;
    CacheBusLockReal(bus,SHARED);
    if (adrs < 0) adrs = ~adrs;
    val = bus->sub->Peek16(bus->sub,adrs);
    //fprintf(stderr,"N2:%X->%X\n",adrs,val);
    return val;
  }
}

static inline void _CacheBusPoke16(CacheBus *bus,int adrs,unsigned short val){
  if (bus->Width == 16 && adrs < 0
      && ~adrs >= bus->Offset && ~adrs < bus->Offset + 2*bus->Length) {
    //fprintf(stderr,"M1:%X->%X\n",~adrs,val);
    bus->ocache[(~adrs-bus->Offset)/2] = val;
    bus->icache[(~adrs-bus->Offset)/2] = 
      bus->icache[(~adrs-bus->Offset)/2] & ~bus->OBit[(~adrs-bus->Offset)/2] 
      | val & bus->OBit[(~adrs-bus->Offset)/2];
  } else {
    if (adrs < 0) adrs = ~adrs;
    //fprintf(stderr,"M2:%X->%X\n",adrs,val);
    CacheBusLockReal(bus,0);
    return bus->sub->Poke16(bus->sub,adrs,val);
  }
}

static inline unsigned _CacheBusPeek32(CacheBus *bus,int adrs){
  if (bus->Width == 32 && adrs < 0
      && ~adrs >= bus->Offset && ~adrs < bus->Offset + 4*bus->Length) {
    return bus->icache[(~adrs-bus->Offset)/4];
  } else {
    if (adrs < 0) adrs = ~adrs;
    CacheBusLockReal(bus,SHARED);
    return bus->sub->Peek32(bus->sub,adrs);
  }
}

static inline void _CacheBusPoke32(CacheBus *bus,int adrs,unsigned val){
  if (bus->Width == 32 && adrs < 0
      && ~adrs >= bus->Offset && ~adrs < bus->Offset + 4*bus->Length) {
    //printf("BC32 %p:[%X]=%X\n",bus->sub,~adrs,val);
    bus->ocache[(~adrs-bus->Offset)/4] = val;
    bus->icache[(~adrs-bus->Offset)/4] = 
      bus->icache[(~adrs-bus->Offset)/4] & ~bus->OBit[(~adrs-bus->Offset)/4] 
      | val & bus->OBit[(~adrs-bus->Offset)/4];
  } else {
    if (adrs < 0) adrs = ~adrs;
    CacheBusLockReal(bus,0);
    return bus->sub->Poke32(bus->sub,adrs,val);
  }
}
//-----------------------------------------------------------------------------
DefinitionFunctionsBit(CacheBus,unsigned char,8)
DefinitionFunctionsBit(CacheBus,unsigned short,16)
DefinitionFunctionsBit(CacheBus,unsigned,32)

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
