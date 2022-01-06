#ifndef __MDIOBus_h
#define __MDIOBus_h
#include "Bus.h"
#include "DIO.h"
#include "Time.h"

typedef struct MDIOBus MDIOBus;

struct MDIOBus {
  Bus;
  int MDC,MDIO;
  unsigned delay;
  DIO *dio;
  Time *time;
};

void *MDIOBusInit(MDIOBus *,void *dio,void *time,int MDC,int MDIO,unsigned delay);
void MDIOBusFini(MDIOBus *);
int MDIOBusLock(MDIOBus *,int,unsigned);
unsigned char MDIOBusPeek8(MDIOBus *,int adrs);
void MDIOBusPoke8(MDIOBus *,int adrs,unsigned char val);
unsigned short MDIOBusPeek16(MDIOBus *,int adrs);
void MDIOBusPoke16(MDIOBus *,int adrs,unsigned short val);
unsigned MDIOBusPeek32(MDIOBus *,int adrs);
void MDIOBusPoke32(MDIOBus *,int adrs,unsigned val);
int MDIOBusBitGet8(MDIOBus *bus,int adrs,int bit);
void MDIOBusBitAssign8(MDIOBus *bus,int adrs,int bit,int val);
void MDIOBusBitSet8(MDIOBus *bus,int adrs,int bit);
void MDIOBusBitClear8(MDIOBus *bus,int adrs,int bit);
int MDIOBusBitGet16(MDIOBus *bus,int adrs,int bit);
void MDIOBusBitAssign16(MDIOBus *bus,int adrs,int bit,int val);
void MDIOBusBitSet16(MDIOBus *bus,int adrs,int bit);
void MDIOBusBitClear16(MDIOBus *bus,int adrs,int bit);
int MDIOBusBitGet32(MDIOBus *bus,int adrs,int bit);
void MDIOBusBitAssign32(MDIOBus *bus,int adrs,int bit,int val);
void MDIOBusBitSet32(MDIOBus *bus,int adrs,int bit);
void MDIOBusBitClear32(MDIOBus *bus,int adrs,int bit);
void MDIOBusPeekStream(MDIOBus *bus,int adr,int dir,char *buf,int len);
void MDIOBusPokeStream(MDIOBus *bus,int adr,int dir,char *buf,int len);
void MDIOBusRefresh(MDIOBus *);
void MDIOBusCommit(MDIOBus *,int forceall);
int MDIOBusBitToggle8(MDIOBus *bus,int adrs,int bit);
int MDIOBusBitToggle16(MDIOBus *bus,int adrs,int bit);
int MDIOBusBitToggle32(MDIOBus *bus,int adrs,int bit);
unsigned char MDIOBusAssign8X(MDIOBus *,int adrs,int bit1,int bit0,int val);
unsigned short MDIOBusAssign16X(MDIOBus *,int adrs,int bit1,int bit0,int val);
unsigned MDIOBusAssign32X(MDIOBus *,int adrs,int bit1,int bit0,int val);
unsigned char MDIOBusBitsGet8(MDIOBus *,int adrs,int bit1,int bit0);
unsigned short MDIOBusBitsGet16(MDIOBus *,int adrs,int bit1,int bit0);
unsigned MDIOBusBitsGet32(MDIOBus *,int adrs,int bit1,int bit0);

#endif
// Author: Michael Schmidt (michael@embeddedTS.com)
// Copyright (c) 2011-2022 Technologic Systems, Inc. dba embeddedTS, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
