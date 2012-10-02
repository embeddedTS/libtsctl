#ifndef __WindowBus_h
#define __WindowBus_h
#include "Bus.h"

typedef struct WindowBus WindowBus;

struct WindowBus {
  Bus;
  Bus *sub; // bus containing the window registers
  int adrs, data; // address of adrs and data registers, respectively
};

void *WindowBusInit(WindowBus *,void *bus,int adrs,int data);
void *WindowBusInit2(WindowBus *,void *mem,int Pages);
void WindowBusFini(WindowBus *);
unsigned char WindowBusPeek8(WindowBus *,int adrs);
void WindowBusPoke8(WindowBus *,int adrs,unsigned char val);
unsigned short WindowBusPeek16(WindowBus *,int adrs);
void WindowBusPoke16(WindowBus *,int adrs,unsigned short val);
unsigned WindowBusPeek32(WindowBus *,int adrs);
void WindowBusPoke32(WindowBus *,int adrs,unsigned val);
int WindowBusBitGet8(WindowBus *bus,int adrs,int bit);
void WindowBusBitAssign8(WindowBus *bus,int adrs,int bit,int val);
void WindowBusBitSet8(WindowBus *bus,int adrs,int bit);
void WindowBusBitClear8(WindowBus *bus,int adrs,int bit);
int WindowBusBitGet16(WindowBus *bus,int adrs,int bit);
void WindowBusBitAssign16(WindowBus *bus,int adrs,int bit,int val);
void WindowBusBitSet16(WindowBus *bus,int adrs,int bit);
void WindowBusBitClear16(WindowBus *bus,int adrs,int bit);
int WindowBusBitGet32(WindowBus *bus,int adrs,int bit);
void WindowBusBitAssign32(WindowBus *bus,int adrs,int bit,int val);
void WindowBusBitSet32(WindowBus *bus,int adrs,int bit);
void WindowBusBitClear32(WindowBus *bus,int adrs,int bit);
void WindowBusPeekStream(WindowBus *bus,int adr,int dir,char* buf);
void WindowBusPokeStream(WindowBus *bus,int adr,int dir,const char* buf);
void WindowBusRefresh(WindowBus *);
void WindowBusCommit(WindowBus *,int forceall);
int WindowBusBitToggle8(WindowBus *bus,int adrs,int bit);
int WindowBusBitToggle16(WindowBus *bus,int adrs,int bit);
int WindowBusBitToggle32(WindowBus *bus,int adrs,int bit);
unsigned char WindowBusAssign8X(WindowBus *,int adrs,int bit1,int bit0,int val);
unsigned short WindowBusAssign16X(WindowBus *,int adrs,int bit1,int bit0,int val);
unsigned WindowBusAssign32X(WindowBus *,int adrs,int bit1,int bit0,int val);
unsigned char WindowBusBitsGet8(WindowBus *,int adrs,int bit1,int bit0);
unsigned short WindowBusBitsGet16(WindowBus *,int adrs,int bit1,int bit0);
unsigned WindowBusBitsGet32(WindowBus *,int adrs,int bit1,int bit0);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
