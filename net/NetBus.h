#ifndef __NetBus_H
#define __NetBus_H
#include "Bus.h"

typedef struct NetBus NetBus;

struct NetBus {
  void *FUNC(Init)(void *me,...);
  void FUNC(Fini)(void *me);
  int FUNC(Lock)(void *me,unsigned num,int flags);
  int FUNC(Unlock)(void *me,unsigned num,int flags);
  int FUNC(Preempt)(void *me);
  unsigned char FUNC(Peek8)(void *me,int Address);
  void FUNC(Poke8)(void *me,int Address,unsigned char Value);
  unsigned short FUNC(Peek16)(void *me,int Address);
  void FUNC(Poke16)(void *me,int Address,unsigned short Value);
  unsigned FUNC(Peek32)(void *me,int Address);
  void FUNC(Poke32)(void *me,int Address,unsigned Value);
  int FUNC(BitGet8)(void *me,int Address,int BitNumber);
  void FUNC(BitAssign8)(void *me,int Address,int BitNumber,int Value);
  void FUNC(BitSet8)(void *me,int Address,int BitNumber);
  void FUNC(BitClear8)(void *me,int Address,int BitNumber);
  int FUNC(BitGet16)(void *me,int Address,int BitNumber);
  void FUNC(BitAssign16)(void *me,int Address,int BitNumber,int Value);
  void FUNC(BitSet16)(void *me,int Address,int BitNumber);
  void FUNC(BitClear16)(void *me,int Address,int BitNumber);
  int FUNC(BitGet32)(void *me,int Address,int BitNumber);
  void FUNC(BitAssign32)(void *me,int Address,int BitNumber,int Value);
  void FUNC(BitSet32)(void *me,int Address,int BitNumber);
  void FUNC(BitClear32)(void *me,int Address,int BitNumber);
  void FUNC(PeekStream)(void *me,int address,int direction,char *dest);
  void FUNC(PokeStream)(void *me,int address,int direction,const char *data);
  void FUNC(Refresh)(void *me);
  void FUNC(Commit)(void *me,int ForceAll);
  int FUNC(BitToggle8)(void *me,int Address,int BitNumber);
  int FUNC(BitToggle16)(void *me,int Address,int BitNumber);
  int FUNC(BitToggle32)(void *me,int Address,int BitNumber);
  unsigned char FUNC(Assign8X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
  unsigned short FUNC(Assign16X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
  unsigned FUNC(Assign32X)(void *me,int Address,int BitMSB,int BitLSB,int Value);
  unsigned char FUNC(BitsGet8)(void *me,int Address,int BitMSB,int BitLSB);
  unsigned short FUNC(BitsGet16)(void *me,int Address,int BitMSB,int BitLSB);
  unsigned FUNC(BitsGet32)(void *me,int Address,int BitMSB,int BitLSB);
  int InitStatus;
  unsigned LockBase;
  int deferlockW;
  int deferlockR;
  tsctl *conn;
  int instance;
  Stream *in,*out;
};
void *NetBusInit(tsctl *,int instance);
void *NetBusFini(NetBus *);
int32 NetBusLock(NetBus *ob,uint32 num,int32 flags);
int32 NetBusUnlock(NetBus *ob,uint32 num,int32 flags);
int32 NetBusPreempt(NetBus *ob);
uint8 NetBusPeek8(NetBus *ob,int32 Address);
void NetBusPoke8(NetBus *ob,int32 Address,uint8 Value);
uint16 NetBusPeek16(NetBus *ob,int32 Address);
void NetBusPoke16(NetBus *ob,int32 Address,uint16 Value);
uint32 NetBusPeek32(NetBus *ob,int32 Address);
void NetBusPoke32(NetBus *ob,int32 Address,uint32 Value);
int32 NetBusBitGet8(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitAssign8(NetBus *ob,int32 Address,int32 BitNumber,int32 Value);
void NetBusBitSet8(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitClear8(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitGet16(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitAssign16(NetBus *ob,int32 Address,int32 BitNumber,int32 Value);
void NetBusBitSet16(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitClear16(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitGet32(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitAssign32(NetBus *ob,int32 Address,int32 BitNumber,int32 Value);
void NetBusBitSet32(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusBitClear32(NetBus *ob,int32 Address,int32 BitNumber);
void NetBusPeekStream(NetBus *ob,int32 address,int32 direction,int8* dest);
void NetBusPokeStream(NetBus *ob,int32 address,int32 direction,const int8* data);
void NetBusRefresh(NetBus *ob);
void NetBusCommit(NetBus *ob,int32 ForceAll);
int32 NetBusBitToggle8(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitToggle16(NetBus *ob,int32 Address,int32 BitNumber);
int32 NetBusBitToggle32(NetBus *ob,int32 Address,int32 BitNumber);
uint8 NetBusAssign8X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value);
uint16 NetBusAssign16X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value);
uint32 NetBusAssign32X(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB,int32 Value);
uint8 NetBusBitsGet8(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB);
uint16 NetBusBitsGet16(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB);
uint32 NetBusBitsGet32(NetBus *ob,int32 Address,int32 BitMSB,int32 BitLSB);
#endif
// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
