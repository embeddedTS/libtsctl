#ifndef __PC104Bus_H
#define __PC104Bus_H
#include "Bus.h"

typedef struct PC104Bus PC104Bus;
struct PC104Bus {
  Bus;
  Bus *sub8, *sub16;
  int offset8,offset16;
  void (*LockCallback)(PC104Bus *,unsigned);
};

void *PC104BusInit(PC104Bus *bus,Bus *sub8,int offset8,Bus *sub16,int offset16,
		   void (*LockCallback)(PC104Bus *,unsigned));
void PC104BusFini(PC104Bus *bus);
unsigned char PC104BusPeek8(PC104Bus *,int adrs);
void PC104BusPoke8(PC104Bus *,int adrs,unsigned char val);
unsigned short PC104BusPeek16(PC104Bus *,int adrs);
void PC104BusPoke16(PC104Bus *,int adrs,unsigned short val);
unsigned PC104BusPeek32(PC104Bus *,int adrs);
void PC104BusPoke32(PC104Bus *,int adrs,unsigned val);
int PC104BusBitGet8(PC104Bus *bus,int adrs,int bit);
void PC104BusBitAssign8(PC104Bus *bus,int adrs,int bit,int val);
void PC104BusBitSet8(PC104Bus *bus,int adrs,int bit);
void PC104BusBitClear8(PC104Bus *bus,int adrs,int bit);
int PC104BusBitGet16(PC104Bus *bus,int adrs,int bit);
void PC104BusBitAssign16(PC104Bus *bus,int adrs,int bit,int val);
void PC104BusBitSet16(PC104Bus *bus,int adrs,int bit);
void PC104BusBitClear16(PC104Bus *bus,int adrs,int bit);
int PC104BusBitGet32(PC104Bus *bus,int adrs,int bit);
void PC104BusBitAssign32(PC104Bus *bus,int adrs,int bit,int val);
void PC104BusBitSet32(PC104Bus *bus,int adrs,int bit);
void PC104BusBitClear32(PC104Bus *bus,int adrs,int bit);
void PC104BusRefresh(PC104Bus *bus);
void PC104BusCommit(PC104Bus *bus,int forceall);
void PC104BusPeekStream(PC104Bus *bus,int adr,int dir,char* buf);
void PC104BusPokeStream(PC104Bus *bus,int adr,int dir,const char* buf);
int PC104BusBitToggle8(PC104Bus *bus,int adrs,int bit);
int PC104BusBitToggle16(PC104Bus *bus,int adrs,int bit);
int PC104BusBitToggle32(PC104Bus *bus,int adrs,int bit);
unsigned char PC104BusAssign8X(PC104Bus *,int adrs,int bit1,int bit0,int val);
unsigned short PC104BusAssign16X(PC104Bus *,int adrs,int bit1,int bit0,int val);
unsigned PC104BusAssign32X(PC104Bus *,int adrs,int bit1,int bit0,int val);
unsigned char PC104BusBitsGet8(PC104Bus *,int adrs,int bit1,int bit0);
unsigned short PC104BusBitsGet16(PC104Bus *,int adrs,int bit1,int bit0);
unsigned PC104BusBitsGet32(PC104Bus *,int adrs,int bit1,int bit0);

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
