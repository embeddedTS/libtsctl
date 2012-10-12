#ifndef __DummyBus_h
#define __DummyBus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct DummyBus DummyBus;
struct DummyBus {
	void *FUNC(Init)(DummyBus *me);
	void FUNC(Fini)(DummyBus *me);
	int FUNC(Lock)(DummyBus *me,unsigned num,int flags);
	int FUNC(Unlock)(DummyBus *me,unsigned num,int flags);
	int FUNC(Preempt)(DummyBus *me);
	unsigned char FUNC(Peek8)(DummyBus *me,int adrs);
	void FUNC(Poke8)(DummyBus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(DummyBus *me,int adrs);
	void FUNC(Poke16)(DummyBus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(DummyBus *me,int adrs);
	void FUNC(Poke32)(DummyBus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(DummyBus *me,int adrs,int bit);
	void FUNC(BitAssign8)(DummyBus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(DummyBus *me,int adrs,int bit);
	void FUNC(BitClear8)(DummyBus *me,int adrs,int bit);
	int FUNC(BitGet16)(DummyBus *me,int adrs,int bit);
	void FUNC(BitAssign16)(DummyBus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(DummyBus *me,int adrs,int bit);
	void FUNC(BitClear16)(DummyBus *me,int adrs,int bit);
	int FUNC(BitGet32)(DummyBus *me,int adrs,int bit);
	void FUNC(BitAssign32)(DummyBus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(DummyBus *me,int adrs,int bit);
	void FUNC(BitClear32)(DummyBus *me,int adrs,int bit);
	void FUNC(PeekStream)(DummyBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(DummyBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(DummyBus *me);
	void FUNC(Commit)(DummyBus *me,int forceall);
	int FUNC(BitToggle8)(DummyBus *me,int adrs,int bit);
	int FUNC(BitToggle16)(DummyBus *me,int adrs,int bit);
	int FUNC(BitToggle32)(DummyBus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(DummyBus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(DummyBus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(DummyBus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(DummyBus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(DummyBus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(DummyBus *me,int adrs,int bit1,int bit0);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	int value;
};

void *DummyBusInit(DummyBus* ob);
void DummyBusFini(DummyBus* ob);
int DummyBusLock(DummyBus* ob,unsigned num,int flags);
int DummyBusUnlock(DummyBus* ob,unsigned num,int flags);
int DummyBusPreempt(DummyBus* ob);
unsigned char DummyBusPeek8(DummyBus* ob,int adrs);
void DummyBusPoke8(DummyBus* ob,int adrs,unsigned char val);
unsigned short DummyBusPeek16(DummyBus* ob,int adrs);
void DummyBusPoke16(DummyBus* ob,int adrs,unsigned short val);
unsigned DummyBusPeek32(DummyBus* ob,int adrs);
void DummyBusPoke32(DummyBus* ob,int adrs,unsigned val);
int DummyBusBitGet8(DummyBus* ob,int adrs,int bit);
void DummyBusBitAssign8(DummyBus* ob,int adrs,int bit,int val);
void DummyBusBitSet8(DummyBus* ob,int adrs,int bit);
void DummyBusBitClear8(DummyBus* ob,int adrs,int bit);
int DummyBusBitGet16(DummyBus* ob,int adrs,int bit);
void DummyBusBitAssign16(DummyBus* ob,int adrs,int bit,int val);
void DummyBusBitSet16(DummyBus* ob,int adrs,int bit);
void DummyBusBitClear16(DummyBus* ob,int adrs,int bit);
int DummyBusBitGet32(DummyBus* ob,int adrs,int bit);
void DummyBusBitAssign32(DummyBus* ob,int adrs,int bit,int val);
void DummyBusBitSet32(DummyBus* ob,int adrs,int bit);
void DummyBusBitClear32(DummyBus* ob,int adrs,int bit);
void DummyBusPeekStream(DummyBus* ob,int address,int direction,char *dest);
void DummyBusPokeStream(DummyBus* ob,int address,int direction,const char *data);
void DummyBusRefresh(DummyBus* ob);
void DummyBusCommit(DummyBus* ob,int forceall);
int DummyBusBitToggle8(DummyBus* ob,int adrs,int bit);
int DummyBusBitToggle16(DummyBus* ob,int adrs,int bit);
int DummyBusBitToggle32(DummyBus* ob,int adrs,int bit);
unsigned char DummyBusAssign8X(DummyBus* ob,int adrs,int bit1,int bit0,int val);
unsigned short DummyBusAssign16X(DummyBus* ob,int adrs,int bit1,int bit0,int val);
unsigned DummyBusAssign32X(DummyBus* ob,int adrs,int bit1,int bit0,int val);
unsigned char DummyBusBitsGet8(DummyBus* ob,int adrs,int bit1,int bit0);
unsigned short DummyBusBitsGet16(DummyBus* ob,int adrs,int bit1,int bit0);
unsigned DummyBusBitsGet32(DummyBus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
