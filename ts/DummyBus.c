#ifndef DummyBus_c
#define DummyBus_c
#include "DummyBus.h"

void *DummyBusInit(DummyBus *bus) {
  if (bus->InitStatus > 0) return bus;
  bus->Init = (void *)DummyBusInit;
  bus->Fini = (void *)DummyBusFini;
  bus->Lock = (void *)DummyBusLock;
  bus->Unlock = (void *)DummyBusUnlock;
  bus->Preempt = (void *)DummyBusPreempt;
  bus->Peek8 = (void *)DummyBusPeek8;
  bus->Poke8 = (void *)DummyBusPoke8;
  bus->Peek16 = (void *)DummyBusPeek16;
  bus->Poke16 = (void *)DummyBusPoke16;
  bus->Peek32 = (void *)DummyBusPeek32;
  bus->Poke32 = (void *)DummyBusPoke32;
  bus->BitGet8 = (void *)DummyBusBitGet8;
  bus->BitAssign8 = (void *)DummyBusBitAssign8;
  bus->BitSet8 = (void *)DummyBusBitSet8;
  bus->BitClear8 = (void *)DummyBusBitClear8;
  bus->BitGet16 = (void *)DummyBusBitGet16;
  bus->BitAssign16 = (void *)DummyBusBitAssign16;
  bus->BitSet16 = (void *)DummyBusBitSet16;
  bus->BitClear16 = (void *)DummyBusBitClear16;
  bus->BitGet32 = (void *)DummyBusBitGet32;
  bus->BitAssign32 = (void *)DummyBusBitAssign32;
  bus->BitSet32 = (void *)DummyBusBitSet32;
  bus->BitClear32 = (void *)DummyBusBitClear32;
  bus->PeekStream = (void *)DummyBusPeekStream;
  bus->PokeStream = (void *)DummyBusPokeStream;
  bus->Refresh = (void *)DummyBusRefresh;
  bus->Commit = (void *)DummyBusCommit;
  bus->BitToggle8 = (void *)DummyBusBitToggle8;
  bus->BitToggle16 = (void *)DummyBusBitToggle16;
  bus->BitToggle32 = (void *)DummyBusBitToggle32;
  bus->Assign8X = (void *)DummyBusAssign8X;
  bus->Assign16X = (void *)DummyBusAssign16X;
  bus->Assign32X = (void *)DummyBusAssign32X;
  bus->BitsGet8 = (void *)DummyBusBitsGet8;
  bus->BitsGet16 = (void *)DummyBusBitsGet16;
  bus->BitsGet32 = (void *)DummyBusBitsGet32;

  bus->InitStatus = 1;
  return bus;
}

void DummyBusFini(DummyBus *bus) {
  if (bus->InitStatus > 0) bus->InitStatus = 0;
}

int DummyBusLock(DummyBus *me,unsigned num,int flags) {
  return 1;
}

int DummyBusUnlock(DummyBus *me,unsigned num,int flags) {
  return 1;
}

int DummyBusPreempt(DummyBus *me) {
  return 1;
}


unsigned char DummyBusPeek8(DummyBus *me,int adrs) {
  return 0;
}

void DummyBusPoke8(DummyBus *me,int adrs,unsigned char val) {
}

unsigned short DummyBusPeek16(DummyBus *me,int adrs) {
  return 0;
}

void DummyBusPoke16(DummyBus *me,int adrs,unsigned short val) {
}

unsigned DummyBusPeek32(DummyBus *me,int adrs) {
  return 0;
}

void DummyBusPoke32(DummyBus *me,int adrs,unsigned val) {
}

int DummyBusBitGet8(DummyBus *bus,int adrs,int bit) {
  return 0;
}

void DummyBusBitAssign8(DummyBus *bus,int adrs,int bit,int val) {
}

void DummyBusBitSet8(DummyBus *bus,int adrs,int bit) {
}

void DummyBusBitClear8(DummyBus *bus,int adrs,int bit) {
}

int DummyBusBitGet16(DummyBus *bus,int adrs,int bit) {
  return 0;
}

void DummyBusBitAssign16(DummyBus *bus,int adrs,int bit,int val) {
}

void DummyBusBitSet16(DummyBus *bus,int adrs,int bit) {
}

void DummyBusBitClear16(DummyBus *bus,int adrs,int bit) {
}

int DummyBusBitGet32(DummyBus *bus,int adrs,int bit) {
  return 0;
}

void DummyBusBitAssign32(DummyBus *bus,int adrs,int bit,int val) {
}

void DummyBusBitSet32(DummyBus *bus,int adrs,int bit) {
}

void DummyBusBitClear32(DummyBus *bus,int adrs,int bit) {
}

void DummyBusPeekStream(DummyBus *bus,int adr,int dir,char* buf) {
}

void DummyBusPokeStream(DummyBus *bus,int adr,int dir,const char* buf) {
}

void DummyBusRefresh(DummyBus *me) {
}

void DummyBusCommit(DummyBus *me,int forceall) {
}

int DummyBusBitToggle8(DummyBus *bus,int adrs,int bit) {
  return 0;
}

int DummyBusBitToggle16(DummyBus *bus,int adrs,int bit) {
  return 0;
}

int DummyBusBitToggle32(DummyBus *bus,int adrs,int bit) {
  return 0;
}

unsigned char DummyBusAssign8X(DummyBus *me,int adrs,int bit1,int bit0,int val) {
  return 0;
}

unsigned short DummyBusAssign16X(DummyBus *me,int adrs,int bit1,int bit0,int val) {
  return 0;
}

unsigned DummyBusAssign32X(DummyBus *me,int adrs,int bit1,int bit0,int val) {
  return 0;
}

unsigned char DummyBusBitsGet8(DummyBus *me,int adrs,int bit1,int bit0) {
  return 0;
}

unsigned short DummyBusBitsGet16(DummyBus *me,int adrs,int bit1,int bit0) {
  return 0;
}

unsigned DummyBusBitsGet32(DummyBus *me,int adrs,int bit1,int bit0) {
  return 0;
}


// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
#endif
