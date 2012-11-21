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
	unsigned char FUNC(Peek8)(WBWindowBus *me,int Address);
	void FUNC(Poke8)(WBWindowBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(WBWindowBus *me,int Address);
	void FUNC(Poke16)(WBWindowBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(WBWindowBus *me,int Address);
	void FUNC(Poke32)(WBWindowBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(WBWindowBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(WBWindowBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(WBWindowBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(WBWindowBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(WBWindowBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(WBWindowBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(WBWindowBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(WBWindowBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(WBWindowBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(WBWindowBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(WBWindowBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(WBWindowBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(WBWindowBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(WBWindowBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(WBWindowBus *me);
	void FUNC(Commit)(WBWindowBus *me,int ForceAll);
	int FUNC(BitToggle8)(WBWindowBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(WBWindowBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(WBWindowBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(WBWindowBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(WBWindowBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(WBWindowBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(WBWindowBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(WBWindowBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(WBWindowBus *me,int Address,int BitMSB,int BitLSB);
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
unsigned char WBWindowBusPeek8(WBWindowBus* ob,int Address);
void WBWindowBusPoke8(WBWindowBus* ob,int Address,unsigned char Value);
unsigned short WBWindowBusPeek16(WBWindowBus* ob,int Address);
void WBWindowBusPoke16(WBWindowBus* ob,int Address,unsigned short Value);
unsigned WBWindowBusPeek32(WBWindowBus* ob,int Address);
void WBWindowBusPoke32(WBWindowBus* ob,int Address,unsigned Value);
int WBWindowBusBitGet8(WBWindowBus* ob,int Address,int BitNumber);
void WBWindowBusBitAssign8(WBWindowBus* ob,int Address,int BitNumber,int Value);
void WBWindowBusBitSet8(WBWindowBus* ob,int Address,int BitNumber);
void WBWindowBusBitClear8(WBWindowBus* ob,int Address,int BitNumber);
int WBWindowBusBitGet16(WBWindowBus* ob,int Address,int BitNumber);
void WBWindowBusBitAssign16(WBWindowBus* ob,int Address,int BitNumber,int Value);
void WBWindowBusBitSet16(WBWindowBus* ob,int Address,int BitNumber);
void WBWindowBusBitClear16(WBWindowBus* ob,int Address,int BitNumber);
int WBWindowBusBitGet32(WBWindowBus* ob,int Address,int BitNumber);
void WBWindowBusBitAssign32(WBWindowBus* ob,int Address,int BitNumber,int Value);
void WBWindowBusBitSet32(WBWindowBus* ob,int Address,int BitNumber);
void WBWindowBusBitClear32(WBWindowBus* ob,int Address,int BitNumber);
void WBWindowBusPeekStream(WBWindowBus* ob,int address,int direction,char *dest);
void WBWindowBusPokeStream(WBWindowBus* ob,int address,int direction,const char *data);
void WBWindowBusRefresh(WBWindowBus* ob);
void WBWindowBusCommit(WBWindowBus* ob,int ForceAll);
int WBWindowBusBitToggle8(WBWindowBus* ob,int Address,int BitNumber);
int WBWindowBusBitToggle16(WBWindowBus* ob,int Address,int BitNumber);
int WBWindowBusBitToggle32(WBWindowBus* ob,int Address,int BitNumber);
unsigned char WBWindowBusAssign8X(WBWindowBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short WBWindowBusAssign16X(WBWindowBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned WBWindowBusAssign32X(WBWindowBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char WBWindowBusBitsGet8(WBWindowBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short WBWindowBusBitsGet16(WBWindowBus* ob,int Address,int BitMSB,int BitLSB);
unsigned WBWindowBusBitsGet32(WBWindowBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
