#ifndef __TSMuxBus_h
#define __TSMuxBus_h
#include "Bus.h"

#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct TSMuxBus TSMuxBus;
struct TSMuxBus {
	void *FUNC(Init)(TSMuxBus *me,void *configbus,int cadrs,void *regbus8,int base8,void *regbus16,int base16);
	void FUNC(Fini)(TSMuxBus *me);
	int FUNC(Lock)(TSMuxBus *me,unsigned num,int flags);
	int FUNC(Unlock)(TSMuxBus *me,unsigned num,int flags);
	int FUNC(Preempt)(TSMuxBus *me);
	unsigned char FUNC(Peek8)(TSMuxBus *me,int Address);
	void FUNC(Poke8)(TSMuxBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(TSMuxBus *me,int Address);
	void FUNC(Poke16)(TSMuxBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(TSMuxBus *me,int Address);
	void FUNC(Poke32)(TSMuxBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(TSMuxBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(TSMuxBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(TSMuxBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(TSMuxBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(TSMuxBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(TSMuxBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(TSMuxBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(TSMuxBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(TSMuxBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(TSMuxBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(TSMuxBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(TSMuxBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(TSMuxBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(TSMuxBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(TSMuxBus *me);
	void FUNC(Commit)(TSMuxBus *me,int ForceAll);
	int FUNC(BitToggle8)(TSMuxBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(TSMuxBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(TSMuxBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(TSMuxBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(TSMuxBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(TSMuxBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(TSMuxBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(TSMuxBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(TSMuxBus *me,int Address,int BitMSB,int BitLSB);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *configbus;
	Bus *regbus8;
	Bus *regbus16;
	int cadrs;
	int base8;
	int base16;
};

void *TSMuxBusInit(TSMuxBus* ob,void *configbus,int cadrs,void *regbus8,int base8,void *regbus16,int base16);
void TSMuxBusFini(TSMuxBus* ob);
int TSMuxBusLock(TSMuxBus* ob,unsigned num,int flags);
int TSMuxBusUnlock(TSMuxBus* ob,unsigned num,int flags);
int TSMuxBusPreempt(TSMuxBus* ob);
unsigned char TSMuxBusPeek8(TSMuxBus* ob,int Address);
void TSMuxBusPoke8(TSMuxBus* ob,int Address,unsigned char Value);
unsigned short TSMuxBusPeek16(TSMuxBus* ob,int Address);
void TSMuxBusPoke16(TSMuxBus* ob,int Address,unsigned short Value);
unsigned TSMuxBusPeek32(TSMuxBus* ob,int Address);
void TSMuxBusPoke32(TSMuxBus* ob,int Address,unsigned Value);
int TSMuxBusBitGet8(TSMuxBus* ob,int Address,int BitNumber);
void TSMuxBusBitAssign8(TSMuxBus* ob,int Address,int BitNumber,int Value);
void TSMuxBusBitSet8(TSMuxBus* ob,int Address,int BitNumber);
void TSMuxBusBitClear8(TSMuxBus* ob,int Address,int BitNumber);
int TSMuxBusBitGet16(TSMuxBus* ob,int Address,int BitNumber);
void TSMuxBusBitAssign16(TSMuxBus* ob,int Address,int BitNumber,int Value);
void TSMuxBusBitSet16(TSMuxBus* ob,int Address,int BitNumber);
void TSMuxBusBitClear16(TSMuxBus* ob,int Address,int BitNumber);
int TSMuxBusBitGet32(TSMuxBus* ob,int Address,int BitNumber);
void TSMuxBusBitAssign32(TSMuxBus* ob,int Address,int BitNumber,int Value);
void TSMuxBusBitSet32(TSMuxBus* ob,int Address,int BitNumber);
void TSMuxBusBitClear32(TSMuxBus* ob,int Address,int BitNumber);
void TSMuxBusPeekStream(TSMuxBus* ob,int address,int direction,char *dest);
void TSMuxBusPokeStream(TSMuxBus* ob,int address,int direction,const char *data);
void TSMuxBusRefresh(TSMuxBus* ob);
void TSMuxBusCommit(TSMuxBus* ob,int ForceAll);
int TSMuxBusBitToggle8(TSMuxBus* ob,int Address,int BitNumber);
int TSMuxBusBitToggle16(TSMuxBus* ob,int Address,int BitNumber);
int TSMuxBusBitToggle32(TSMuxBus* ob,int Address,int BitNumber);
unsigned char TSMuxBusAssign8X(TSMuxBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short TSMuxBusAssign16X(TSMuxBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned TSMuxBusAssign32X(TSMuxBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char TSMuxBusBitsGet8(TSMuxBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short TSMuxBusBitsGet16(TSMuxBus* ob,int Address,int BitMSB,int BitLSB);
unsigned TSMuxBusBitsGet32(TSMuxBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
