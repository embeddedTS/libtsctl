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
	unsigned char FUNC(Peek8)(DummyBus *me,int Address);
	void FUNC(Poke8)(DummyBus *me,int Address,unsigned char Value);
	unsigned short FUNC(Peek16)(DummyBus *me,int Address);
	void FUNC(Poke16)(DummyBus *me,int Address,unsigned short Value);
	unsigned FUNC(Peek32)(DummyBus *me,int Address);
	void FUNC(Poke32)(DummyBus *me,int Address,unsigned Value);
	int FUNC(BitGet8)(DummyBus *me,int Address,int BitNumber);
	void FUNC(BitAssign8)(DummyBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet8)(DummyBus *me,int Address,int BitNumber);
	void FUNC(BitClear8)(DummyBus *me,int Address,int BitNumber);
	int FUNC(BitGet16)(DummyBus *me,int Address,int BitNumber);
	void FUNC(BitAssign16)(DummyBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet16)(DummyBus *me,int Address,int BitNumber);
	void FUNC(BitClear16)(DummyBus *me,int Address,int BitNumber);
	int FUNC(BitGet32)(DummyBus *me,int Address,int BitNumber);
	void FUNC(BitAssign32)(DummyBus *me,int Address,int BitNumber,int Value);
	void FUNC(BitSet32)(DummyBus *me,int Address,int BitNumber);
	void FUNC(BitClear32)(DummyBus *me,int Address,int BitNumber);
	void FUNC(PeekStream)(DummyBus *me,int address,int direction,char *dest);
	void FUNC(PokeStream)(DummyBus *me,int address,int direction,const char *data);
	void FUNC(Refresh)(DummyBus *me);
	void FUNC(Commit)(DummyBus *me,int ForceAll);
	int FUNC(BitToggle8)(DummyBus *me,int Address,int BitNumber);
	int FUNC(BitToggle16)(DummyBus *me,int Address,int BitNumber);
	int FUNC(BitToggle32)(DummyBus *me,int Address,int BitNumber);
	unsigned char FUNC(Assign8X)(DummyBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned short FUNC(Assign16X)(DummyBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned FUNC(Assign32X)(DummyBus *me,int Address,int BitMSB,int BitLSB,int Value);
	unsigned char FUNC(BitsGet8)(DummyBus *me,int Address,int BitMSB,int BitLSB);
	unsigned short FUNC(BitsGet16)(DummyBus *me,int Address,int BitMSB,int BitLSB);
	unsigned FUNC(BitsGet32)(DummyBus *me,int Address,int BitMSB,int BitLSB);
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
unsigned char DummyBusPeek8(DummyBus* ob,int Address);
void DummyBusPoke8(DummyBus* ob,int Address,unsigned char Value);
unsigned short DummyBusPeek16(DummyBus* ob,int Address);
void DummyBusPoke16(DummyBus* ob,int Address,unsigned short Value);
unsigned DummyBusPeek32(DummyBus* ob,int Address);
void DummyBusPoke32(DummyBus* ob,int Address,unsigned Value);
int DummyBusBitGet8(DummyBus* ob,int Address,int BitNumber);
void DummyBusBitAssign8(DummyBus* ob,int Address,int BitNumber,int Value);
void DummyBusBitSet8(DummyBus* ob,int Address,int BitNumber);
void DummyBusBitClear8(DummyBus* ob,int Address,int BitNumber);
int DummyBusBitGet16(DummyBus* ob,int Address,int BitNumber);
void DummyBusBitAssign16(DummyBus* ob,int Address,int BitNumber,int Value);
void DummyBusBitSet16(DummyBus* ob,int Address,int BitNumber);
void DummyBusBitClear16(DummyBus* ob,int Address,int BitNumber);
int DummyBusBitGet32(DummyBus* ob,int Address,int BitNumber);
void DummyBusBitAssign32(DummyBus* ob,int Address,int BitNumber,int Value);
void DummyBusBitSet32(DummyBus* ob,int Address,int BitNumber);
void DummyBusBitClear32(DummyBus* ob,int Address,int BitNumber);
void DummyBusPeekStream(DummyBus* ob,int address,int direction,char *dest);
void DummyBusPokeStream(DummyBus* ob,int address,int direction,const char *data);
void DummyBusRefresh(DummyBus* ob);
void DummyBusCommit(DummyBus* ob,int ForceAll);
int DummyBusBitToggle8(DummyBus* ob,int Address,int BitNumber);
int DummyBusBitToggle16(DummyBus* ob,int Address,int BitNumber);
int DummyBusBitToggle32(DummyBus* ob,int Address,int BitNumber);
unsigned char DummyBusAssign8X(DummyBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned short DummyBusAssign16X(DummyBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned DummyBusAssign32X(DummyBus* ob,int Address,int BitMSB,int BitLSB,int Value);
unsigned char DummyBusBitsGet8(DummyBus* ob,int Address,int BitMSB,int BitLSB);
unsigned short DummyBusBitsGet16(DummyBus* ob,int Address,int BitMSB,int BitLSB);
unsigned DummyBusBitsGet32(DummyBus* ob,int Address,int BitMSB,int BitLSB);
#endif

// Author: Michael Schmidt (michael@embeddedARM.com)
// Copyright (c) 2012, Technologic Systems, All Rights Reserved
// Refer to the COPYRIGHT file provided with this project for licensing terms.
