#ifndef __Cavium2132SBus_h
#define __Cavium2132SBus_h
#include "Bus.h"

typedef struct Cavium2132SBus Cavium2132SBus ;
struct Cavium2132SBus {
  Bus;
  Bus *spibus;
  Bus *gpiobus;
  int gotHUP;
  int last_gpio_adr;
};

void *Cavium2132SBusInit(Cavium2132SBus *,void *spibus,void *gpiobus);
void Cavium2132SBusFini(Cavium2132SBus *);
unsigned char Cavium2132SBusPeek8(Cavium2132SBus *,int adrs);
void Cavium2132SBusPoke8(Cavium2132SBus *,int adrs,unsigned char val);
unsigned short Cavium2132SBusPeek16(Cavium2132SBus *,int adrs);
void Cavium2132SBusPoke16(Cavium2132SBus *,int adrs,unsigned short val);
unsigned Cavium2132SBusPeek32(Cavium2132SBus *,int adrs);
void Cavium2132SBusPoke32(Cavium2132SBus *,int adrs,unsigned val);
int Cavium2132SBusBitGet8(Cavium2132SBus *bus,int adrs,int bit);
void Cavium2132SBusBitAssign8(Cavium2132SBus *bus,int adrs,int bit,int val);
void Cavium2132SBusBitSet8(Cavium2132SBus *bus,int adrs,int bit);
void Cavium2132SBusBitClear8(Cavium2132SBus *bus,int adrs,int bit);
int Cavium2132SBusBitGet16(Cavium2132SBus *bus,int adrs,int bit);
void Cavium2132SBusBitAssign16(Cavium2132SBus *bus,int adrs,int bit,int val);
void Cavium2132SBusBitSet16(Cavium2132SBus *bus,int adrs,int bit);
void Cavium2132SBusBitClear16(Cavium2132SBus *bus,int adrs,int bit);
int Cavium2132SBusBitGet32(Cavium2132SBus *bus,int adrs,int bit);
void Cavium2132SBusBitAssign32(Cavium2132SBus *bus,int adrs,int bit,int val);
void Cavium2132SBusBitSet32(Cavium2132SBus *bus,int adrs,int bit);
void Cavium2132SBusBitClear32(Cavium2132SBus *bus,int adrs,int bit);
void Cavium2132SBusPeekStream(Cavium2132SBus *bus,int adr,int dir,char* buf);
void Cavium2132SBusPokeStream(Cavium2132SBus *bus,int adr,int dir,const char *buf);
void Cavium2132SBusRefresh(Cavium2132SBus *);
void Cavium2132SBusCommit(Cavium2132SBus *,int forceall);
int Cavium2132SBusBitToggle8(Cavium2132SBus *bus,int adrs,int bit);
int Cavium2132SBusBitToggle16(Cavium2132SBus *bus,int adrs,int bit);
int Cavium2132SBusBitToggle32(Cavium2132SBus *bus,int adrs,int bit);
unsigned char Cavium2132SBusAssign8X(Cavium2132SBus *,int adrs,int bit1,int bit0,int val);
unsigned short Cavium2132SBusAssign16X(Cavium2132SBus *,int adrs,int bit1,int bit0,int val);
unsigned Cavium2132SBusAssign32X(Cavium2132SBus *,int adrs,int bit1,int bit0,int val);
unsigned char Cavium2132SBusBitsGet8(Cavium2132SBus *,int adrs,int bit1,int bit0);
unsigned short Cavium2132SBusBitsGet16(Cavium2132SBus *,int adrs,int bit1,int bit0);
unsigned Cavium2132SBusBitsGet32(Cavium2132SBus *,int adrs,int bit1,int bit0);

enum {
  Cavium2132SBusErrorMapping=-100
};

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
