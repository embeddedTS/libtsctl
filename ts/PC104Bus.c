#ifndef PC104Bus_c
#define PC104Bus_c
#include "Bit.h"
#include "PC104Bus.h"

static void PC104BusLockCallback(PC104Bus *bus,unsigned num) {
  if (bus->LockCallback) bus->LockCallback(bus,num);
}

#define LOCK_TYPE_SHARED
#define LOCK_CLASS PC104Bus
#define LOCK_CALLBACK PC104BusLockCallback
#include "TSLock.h"

void *PC104BusInit(PC104Bus *bus,Bus *sub8,int offset8,Bus *sub16,int offset16,
		   void (*LockCallback)(PC104Bus *,unsigned)) {
  if (bus->InitStatus > 0) return bus;
  if (sub8->InitStatus <= 0 || sub16->InitStatus <= 0) return bus;

  bus->sub8 = sub8;
  bus->sub16 = sub16;
  bus->offset8 = offset8;
  bus->offset16 = offset16;
  bus->LockCallback = LockCallback;
  bus->Init = (void *)PC104BusInit;
  bus->Fini = (void *)PC104BusFini;
  bus->Lock = (void *)PC104BusLock;
  bus->Unlock = (void *)PC104BusUnlock;
  bus->Preempt = (void *)PC104BusPreempt;
  bus->Peek8 = (void *)PC104BusPeek8;
  bus->Poke8 = (void *)PC104BusPoke8;
  bus->Peek16 = (void *)PC104BusPeek16;
  bus->Poke16 = (void *)PC104BusPoke16;
  bus->Peek32 = (void *)PC104BusPeek32;
  bus->Poke32 = (void *)PC104BusPoke32;
  bus->BitGet8 = (void *)PC104BusBitGet8;
  bus->BitAssign8 = (void *)PC104BusBitAssign8;
  bus->BitSet8 = (void *)PC104BusBitSet8;
  bus->BitClear8 = (void *)PC104BusBitClear8;
  bus->BitGet16 = (void *)PC104BusBitGet16;
  bus->BitAssign16 = (void *)PC104BusBitAssign16;
  bus->BitSet16 = (void *)PC104BusBitSet16;
  bus->BitClear16 = (void *)PC104BusBitClear16;
  bus->BitGet32 = (void *)PC104BusBitGet32;
  bus->BitAssign32 = (void *)PC104BusBitAssign32;
  bus->BitSet32 = (void *)PC104BusBitSet32;
  bus->BitClear32 = (void *)PC104BusBitClear32;
  bus->PeekStream = (void *)PC104BusPeekStream;
  bus->PokeStream = (void *)PC104BusPokeStream;
  bus->Refresh = (void *)PC104BusRefresh;
  bus->Commit = (void *)PC104BusCommit;
  bus->BitToggle8 = (void *)PC104BusBitToggle8;
  bus->BitToggle16 = (void *)PC104BusBitToggle16;
  bus->BitToggle32 = (void *)PC104BusBitToggle32;
  bus->Assign8X = (void *)PC104BusAssign8X;
  bus->Assign16X = (void *)PC104BusAssign16X;
  bus->Assign32X = (void *)PC104BusAssign32X;
  bus->BitsGet8 = (void *)PC104BusBitsGet8;
  bus->BitsGet16 = (void *)PC104BusBitsGet16;
  bus->BitsGet32 = (void *)PC104BusBitsGet32;
  
  PC104BusLockInit(bus,1);
  bus->InitStatus = 1;
  return bus;
}

void PC104BusFini(PC104Bus *bus) {
  bus->InitStatus = 0;
}

void PC104BusRefresh(PC104Bus *bus) {
  bus->sub8->Refresh(bus->sub8);
}

void PC104BusCommit(PC104Bus *bus,int forceall) {
  bus->sub16->Commit(bus->sub16,forceall);
}

void PC104BusPeekStream(PC104Bus *bus,int adr,int dir,char* buf) {
  bus->sub8->PeekStream(bus->sub8,adr+bus->offset8,dir,buf);
}

void PC104BusPokeStream(PC104Bus *bus,int adr,int dir,const char* buf) {
  bus->sub8->PokeStream(bus->sub8,adr+bus->offset8,dir,buf);
}

static inline unsigned char _PC104BusPeek8(PC104Bus *bus,int adrs){
  return bus->sub8->Peek8(bus->sub8,adrs+bus->offset8);
}

static inline void _PC104BusPoke8(PC104Bus *bus,int adrs,unsigned char val){
  return bus->sub8->Poke8(bus->sub8,adrs+bus->offset8,val);
}

static inline unsigned short _PC104BusPeek16(PC104Bus *bus,int adrs){
  return bus->sub16->Peek16(bus->sub16,adrs+bus->offset16);
}

static inline void _PC104BusPoke16(PC104Bus *bus,int adrs,unsigned short val){
  return bus->sub16->Poke16(bus->sub16,adrs+bus->offset16,val);
}

static inline unsigned _PC104BusPeek32(PC104Bus *bus,int adrs){
  return 0;
}

static inline void _PC104BusPoke32(PC104Bus *bus,int adrs,unsigned val){
}

DefinitionFunctionsBit(PC104Bus,unsigned char,8)
DefinitionFunctionsBit(PC104Bus,unsigned short,16)
DefinitionFunctionsBit(PC104Bus,unsigned,32)

// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2012-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
