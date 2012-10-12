#ifndef __WBWindowBus_h
#define __WBWindowBus_h
#undef FUNC
#ifndef SWIGGY
#define FUNC(x) (*x)
#else
#define FUNC(x) x
#endif

typedef struct WBWindowBus WBWindowBus;
struct WBWindowBus {
	void *FUNC(Init)(WBWindowBus *me,void *bus,int adrs,int offset);
	void FUNC(Fini)(WBWindowBus *me);
	int FUNC(Lock)(WBWindowBus *me,unsigned num,int flags);
	int FUNC(Unlock)(WBWindowBus *me,unsigned num,int flags);
	int FUNC(Preempt)(WBWindowBus *me);
	unsigned char FUNC(Peek8)(WBWindowBus *me,int adrs);
	void FUNC(Poke8)(WBWindowBus *me,int adrs,unsigned char val);
	unsigned short FUNC(Peek16)(WBWindowBus *me,int adrs);
	void FUNC(Poke16)(WBWindowBus *me,int adrs,unsigned short val);
	unsigned FUNC(Peek32)(WBWindowBus *me,int adrs);
	void FUNC(Poke32)(WBWindowBus *me,int adrs,unsigned val);
	int FUNC(BitGet8)(WBWindowBus *me,int adrs,int bit);
	void FUNC(BitAssign8)(WBWindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet8)(WBWindowBus *me,int adrs,int bit);
	void FUNC(BitClear8)(WBWindowBus *me,int adrs,int bit);
	int FUNC(BitGet16)(WBWindowBus *me,int adrs,int bit);
	void FUNC(BitAssign16)(WBWindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet16)(WBWindowBus *me,int adrs,int bit);
	void FUNC(BitClear16)(WBWindowBus *me,int adrs,int bit);
	int FUNC(BitGet32)(WBWindowBus *me,int adrs,int bit);
	void FUNC(BitAssign32)(WBWindowBus *me,int adrs,int bit,int val);
	void FUNC(BitSet32)(WBWindowBus *me,int adrs,int bit);
	void FUNC(BitClear32)(WBWindowBus *me,int adrs,int bit);
	void FUNC(PeekStream)(WBWindowBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(WBWindowBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(WBWindowBus *me);
	void FUNC(Commit)(WBWindowBus *me,int forceall);
	int FUNC(BitToggle8)(WBWindowBus *me,int adrs,int bit);
	int FUNC(BitToggle16)(WBWindowBus *me,int adrs,int bit);
	int FUNC(BitToggle32)(WBWindowBus *me,int adrs,int bit);
	unsigned char FUNC(Assign8X)(WBWindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned short FUNC(Assign16X)(WBWindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned FUNC(Assign32X)(WBWindowBus *me,int adrs,int bit1,int bit0,int val);
	unsigned char FUNC(BitsGet8)(WBWindowBus *me,int adrs,int bit1,int bit0);
	unsigned short FUNC(BitsGet16)(WBWindowBus *me,int adrs,int bit1,int bit0);
	unsigned FUNC(BitsGet32)(WBWindowBus *me,int adrs,int bit1,int bit0);
	int InitStatus;
	unsigned LockBase;
	int deferlockW;
	int deferlockR;
	Bus *sub;
	int adrs;
	int offset;
};

void *WBWindowBusInit(WBWindowBus* ob,void *bus,int adrs,int offset);
void WBWindowBusFini(WBWindowBus* ob);
int WBWindowBusLock(WBWindowBus* ob,unsigned num,int flags);
int WBWindowBusUnlock(WBWindowBus* ob,unsigned num,int flags);
int WBWindowBusPreempt(WBWindowBus* ob);
unsigned char WBWindowBusPeek8(WBWindowBus* ob,int adrs);
void WBWindowBusPoke8(WBWindowBus* ob,int adrs,unsigned char val);
unsigned short WBWindowBusPeek16(WBWindowBus* ob,int adrs);
void WBWindowBusPoke16(WBWindowBus* ob,int adrs,unsigned short val);
unsigned WBWindowBusPeek32(WBWindowBus* ob,int adrs);
void WBWindowBusPoke32(WBWindowBus* ob,int adrs,unsigned val);
int WBWindowBusBitGet8(WBWindowBus* ob,int adrs,int bit);
void WBWindowBusBitAssign8(WBWindowBus* ob,int adrs,int bit,int val);
void WBWindowBusBitSet8(WBWindowBus* ob,int adrs,int bit);
void WBWindowBusBitClear8(WBWindowBus* ob,int adrs,int bit);
int WBWindowBusBitGet16(WBWindowBus* ob,int adrs,int bit);
void WBWindowBusBitAssign16(WBWindowBus* ob,int adrs,int bit,int val);
void WBWindowBusBitSet16(WBWindowBus* ob,int adrs,int bit);
void WBWindowBusBitClear16(WBWindowBus* ob,int adrs,int bit);
int WBWindowBusBitGet32(WBWindowBus* ob,int adrs,int bit);
void WBWindowBusBitAssign32(WBWindowBus* ob,int adrs,int bit,int val);
void WBWindowBusBitSet32(WBWindowBus* ob,int adrs,int bit);
void WBWindowBusBitClear32(WBWindowBus* ob,int adrs,int bit);
void WBWindowBusPeekStream(WBWindowBus* ob,int address,int direction,char *dest);
void WBWindowBusPokeStream(WBWindowBus* ob,int address,int direction,const char *data);
void WBWindowBusRefresh(WBWindowBus* ob);
void WBWindowBusCommit(WBWindowBus* ob,int forceall);
int WBWindowBusBitToggle8(WBWindowBus* ob,int adrs,int bit);
int WBWindowBusBitToggle16(WBWindowBus* ob,int adrs,int bit);
int WBWindowBusBitToggle32(WBWindowBus* ob,int adrs,int bit);
unsigned char WBWindowBusAssign8X(WBWindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned short WBWindowBusAssign16X(WBWindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned WBWindowBusAssign32X(WBWindowBus* ob,int adrs,int bit1,int bit0,int val);
unsigned char WBWindowBusBitsGet8(WBWindowBus* ob,int adrs,int bit1,int bit0);
unsigned short WBWindowBusBitsGet16(WBWindowBus* ob,int adrs,int bit1,int bit0);
unsigned WBWindowBusBitsGet32(WBWindowBus* ob,int adrs,int bit1,int bit0);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
