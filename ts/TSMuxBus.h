#ifndef __TSMuxBus_h
#define __TSMuxBus_h
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
	unsigned char FUNC(Peek8)(TSMuxBus *me,int adrs);
	void FUNC(Poke8)(TSMuxBus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(TSMuxBus *me,int adrs);
	void FUNC(Poke16)(TSMuxBus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(TSMuxBus *me,int adrs);
	void FUNC(Poke32)(TSMuxBus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(TSMuxBus *me,int adrs,int bit);
	void FUNC(BitAssign8)(TSMuxBus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(TSMuxBus *me,int adrs,int bit);
	void FUNC(BitClear8)(TSMuxBus *me,int adrs,int bit);
	int FUNC(BitGet16)(TSMuxBus *me,int adrs,int bit);
	void FUNC(BitAssign16)(TSMuxBus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(TSMuxBus *me,int adrs,int bit);
	void FUNC(BitClear16)(TSMuxBus *me,int adrs,int bit);
	int FUNC(BitGet32)(TSMuxBus *me,int adrs,int bit);
	void FUNC(BitAssign32)(TSMuxBus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(TSMuxBus *me,int adrs,int bit);
	void FUNC(BitClear32)(TSMuxBus *me,int adrs,int bit);
	void FUNC(PeekStream)(TSMuxBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(TSMuxBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(TSMuxBus *me);
	void FUNC(Commit)(TSMuxBus *me,int forceall);
	int FUNC(BitToggle8)(TSMuxBus *me,int adrs,int bit);
	int FUNC(BitToggle16)(TSMuxBus *me,int adrs,int bit);
	int FUNC(BitToggle32)(TSMuxBus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(TSMuxBus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(TSMuxBus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(TSMuxBus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(TSMuxBus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(TSMuxBus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(TSMuxBus *me,int adrs,int bit1,int bit0);
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
unsigned char TSMuxBusPeek8(TSMuxBus* ob,int adrs);
void TSMuxBusPoke8(TSMuxBus* ob,int adrs,unsigned char val);
unsigned short TSMuxBusPeek16(TSMuxBus* ob,int adrs);
void TSMuxBusPoke16(TSMuxBus* ob,int adrs,unsigned short val);
unsigned TSMuxBusPeek32(TSMuxBus* ob,int adrs);
void TSMuxBusPoke32(TSMuxBus* ob,int adrs,unsigned val);
int TSMuxBusBitGet8(TSMuxBus* ob,int adrs,int bit);
void TSMuxBusBitAssign8(TSMuxBus* ob,int adrs,int bit,int val);
void TSMuxBusBitSet8(TSMuxBus* ob,int adrs,int bit);
void TSMuxBusBitClear8(TSMuxBus* ob,int adrs,int bit);
int TSMuxBusBitGet16(TSMuxBus* ob,int adrs,int bit);
void TSMuxBusBitAssign16(TSMuxBus* ob,int adrs,int bit,int val);
void TSMuxBusBitSet16(TSMuxBus* ob,int adrs,int bit);
void TSMuxBusBitClear16(TSMuxBus* ob,int adrs,int bit);
int TSMuxBusBitGet32(TSMuxBus* ob,int adrs,int bit);
void TSMuxBusBitAssign32(TSMuxBus* ob,int adrs,int bit,int val);
void TSMuxBusBitSet32(TSMuxBus* ob,int adrs,int bit);
void TSMuxBusBitClear32(TSMuxBus* ob,int adrs,int bit);
void TSMuxBusPeekStream(TSMuxBus* ob,int address,int direction,char *dest);
void TSMuxBusPokeStream(TSMuxBus* ob,int address,int direction,const char *data);
void TSMuxBusRefresh(TSMuxBus* ob);
void TSMuxBusCommit(TSMuxBus* ob,int forceall);
int TSMuxBusBitToggle8(TSMuxBus* ob,int adrs,int bit);
int TSMuxBusBitToggle16(TSMuxBus* ob,int adrs,int bit);
int TSMuxBusBitToggle32(TSMuxBus* ob,int adrs,int bit);
unsigned char TSMuxBusAssign8X(TSMuxBus* ob,int adrs,int bit1,int bit0,int val);
unsigned short TSMuxBusAssign16X(TSMuxBus* ob,int adrs,int bit1,int bit0,int val);
unsigned TSMuxBusAssign32X(TSMuxBus* ob,int adrs,int bit1,int bit0,int val);
unsigned char TSMuxBusBitsGet8(TSMuxBus* ob,int adrs,int bit1,int bit0);
unsigned short TSMuxBusBitsGet16(TSMuxBus* ob,int adrs,int bit1,int bit0);
unsigned TSMuxBusBitsGet32(TSMuxBus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
