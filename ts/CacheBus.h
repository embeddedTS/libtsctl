#ifndef __CacheBus_H
#define __CacheBus_H
#include "Bus.h"

typedef struct CacheBus CacheBus;
struct CacheBus {
  Bus;
  Bus *sub;
  unsigned Length; // number of addresses to cache from start (was len)
  unsigned Width; // bit of bus to cache (was width), must be 8, 16, or 32
  unsigned Offset; // offset from base address to start caching (was offset)
  unsigned *icache,*ocache,*ocache0; // caller allocated, sizeof(unsigned) * Length
  unsigned *WO, *IBit,*OBit; // caller allocated and initialized, sizeof(unsigned) * Length
};

/*
CacheBus bus0;
unsigned wo[16],ibit[16],obit[16];
unsigned icache[16],ocache[16],ocache0[16];
...
CacheBusPreInit(&bus0);
bus0.sub = &bus1; // or whatever
bus0.Length = 16;
bus0.Width=32;
bus0.Offset=0;
bus0.WO = wo;
bus0.Ibit = ibit;
bus0.Obit = obit;
bus0.icache = icache;
bus0.ocache = ocache;
bus0.ocache0 = ocache0;
bus0.IBit[6]=0xFFFFFFFF;
bus0.IBit[15]=0xFFFFFFFF;
bus0.OBit[0]=0xFFFFFFFF;
bus0.OBit[4]=0xFFFFFFFF;
bus0.OBit[5]=0xFFFFFFFF;
bus0.OBit[12]=0xFFFFFFFF;
bus0.OBit[13]=0xFFFFFFFF;
bus0.WO[0]=0xFFFFFFFF;
bus0.WO[1]=0xFFFFFFFF;
bus0.WO[4]=0xFFFFFFFF;
bus0.WO[5]=0xFFFFFFFF;
bus0.WO[8]=0xFFFFFFFF;
bus0.WO[9]=0xFFFFFFFF;
*/

void *CacheBusInit(CacheBus *bus,void *bus1);
void CacheBusFini(CacheBus *bus);
unsigned char CacheBusPeek8(CacheBus *,int adrs);
void CacheBusPoke8(CacheBus *,int adrs,unsigned char val);
unsigned short CacheBusPeek16(CacheBus *,int adrs);
void CacheBusPoke16(CacheBus *,int adrs,unsigned short val);
unsigned CacheBusPeek32(CacheBus *,int adrs);
void CacheBusPoke32(CacheBus *,int adrs,unsigned val);
int CacheBusBitGet8(CacheBus *bus,int adrs,int bit);
void CacheBusBitAssign8(CacheBus *bus,int adrs,int bit,int val);
void CacheBusBitSet8(CacheBus *bus,int adrs,int bit);
void CacheBusBitClear8(CacheBus *bus,int adrs,int bit);
int CacheBusBitGet16(CacheBus *bus,int adrs,int bit);
void CacheBusBitAssign16(CacheBus *bus,int adrs,int bit,int val);
void CacheBusBitSet16(CacheBus *bus,int adrs,int bit);
void CacheBusBitClear16(CacheBus *bus,int adrs,int bit);
int CacheBusBitGet32(CacheBus *bus,int adrs,int bit);
void CacheBusBitAssign32(CacheBus *bus,int adrs,int bit,int val);
void CacheBusBitSet32(CacheBus *bus,int adrs,int bit);
void CacheBusBitClear32(CacheBus *bus,int adrs,int bit);
void CacheBusRefresh(CacheBus *bus);
void CacheBusCommit(CacheBus *bus,int forceall);
void CacheBusPeekStream(CacheBus *bus,int adr,int dir,char* buf);
void CacheBusPokeStream(CacheBus *bus,int adr,int dir,const char* buf);
int CacheBusBitToggle8(CacheBus *bus,int adrs,int bit);
int CacheBusBitToggle16(CacheBus *bus,int adrs,int bit);
int CacheBusBitToggle32(CacheBus *bus,int adrs,int bit);
unsigned char CacheBusAssign8X(CacheBus *,int adrs,int bit1,int bit0,int val);
unsigned short CacheBusAssign16X(CacheBus *,int adrs,int bit1,int bit0,int val);
unsigned CacheBusAssign32X(CacheBus *,int adrs,int bit1,int bit0,int val);
unsigned char CacheBusBitsGet8(CacheBus *,int adrs,int bit1,int bit0);
unsigned short CacheBusBitsGet16(CacheBus *,int adrs,int bit1,int bit0);
unsigned CacheBusBitsGet32(CacheBus *,int adrs,int bit1,int bit0);

enum {
  CacheBusErrorWidthInvalid=-100
};

#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2011, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
